//
// Created by timpo on 29/04/24.
//
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "main.h"


int main(int argc, char *argv[]) {
    int argsCount = getCountArgs(argc, argv);
    if (argc <= 1 || argsCount == 0 || argsCount > 2) {
        fprintf(stderr, "usage: ./sparse [input] output [-b block_size]\n");
        return -1;
    }

    bool hasInput = argsCount == 2;

    char *inputFilename = hasInput ? argv[1] : NULL;
    char *outputFilename = hasInput ? argv[2] : argv[1];
    int blocksize = getBlockSize(argc, argv);

    return create_sparse(inputFilename, outputFilename, blocksize);
}

int getCountArgs(int argc, char *argv[]) {
    int countBeforeOptional = 0;
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') break;
        countBeforeOptional++;
    }
    return countBeforeOptional;
}


int getBlockSize(int argc, char *argv[]) {
    int blocksize = 4096;

    int blockSizeArgument = getopt(argc, argv, "b:");
    if (blockSizeArgument == 'b') {
        return atoi(optarg);
    }
    return blocksize;
}

int create_sparse(char *inputFile, char *outputFile, int blocksize) {
    int output = open(outputFile, (O_CREAT | O_WRONLY), (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
    if (output == -1) {
        return -1;
    }

    int input = -1;
    if (inputFile == NULL) {
        input = STDIN_FILENO;
    } else {
        input = open(inputFile, O_RDONLY);
    }

    if (input == -1) {
        return -1;
    }

    int res;

    res = process(input, output, blocksize);
    if (res == -1) {
        return -1;
    }
    res = close(output);
    if (res == -1) return -1;

    if (input != STDIN_FILENO) {
        res = close(input);
        if (res == -1) return -1;
    }
    return 0;
}

int process(int input, int output, int blocksize) {
    char buffer[blocksize];
    for (int i = 0; i < blocksize; ++i) {
        buffer[i] = 0;
    }

    int res;

    size_t totalReaded = 0;
    while (true) {
        int readed = read(input, buffer, blocksize);

        if (readed == -1) {
            return -1;
        }

        if (readed == 0) {
            break;
        }

        totalReaded += readed;

        bool onlyZeroes = true;
        for (int i = 0; i < readed; ++i) {
            if (buffer[i] != 0) {
                onlyZeroes = false;
                break;
            }
        }

        if (onlyZeroes) {
            res = lseek(output, readed, SEEK_CUR);
            if (res == -1) return -1;
        } else {
            res = write(output, buffer, readed);

            if (res == -1) return -1;
        }
    }

    if (res == -1) return -1;

    return 0;
}