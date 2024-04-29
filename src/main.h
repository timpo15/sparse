//
// Created by timpo on 29/04/24.
//

#ifndef SPARSE_MAIN_H
#define SPARSE_MAIN_H

#endif //SPARSE_MAIN_H

int getCountArgs(int argc, char * argv[]);
int getBlockSize(int argc, char * argv[]);
int create_sparse(char * inputFilename, char * outputFilename, int blockSize);
int process(int input, int output, int blocksize);
