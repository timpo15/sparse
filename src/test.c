//
// Created by timpo on 29/04/24.
//
#include <unistd.h>
#include <fcntl.h>

#include <sys/stat.h>
#include <stdio.h>

const unsigned int BUFFER_SIZE = 4 * 1024 * 1024 + 1;
unsigned const char one[1] = {1};


int main(void) {
    int file = open("A", (O_CREAT | O_WRONLY), (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH));
    if (file == -1) {
        perror("Failed to create test file: ");
        return -1;
    }

    int res = ftruncate(file, BUFFER_SIZE);
    if (res == -1) {
        perror("Failed to fill test file");
        return -1;
    }
    lseek(file, 0, SEEK_SET);
    write(file, one, 1);

    lseek(file, 10000, SEEK_SET);
    write(file, one, 1);

    lseek(file, -1, SEEK_END);
    write(file, one, 1);

    close(file);
    return 0;
}