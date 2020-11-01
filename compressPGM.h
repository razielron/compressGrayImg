#ifndef COMPRESS_PGM
#define COMPRESS_PGM

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include "allSegments.h"
#include "segment.h"
#include "bitMap.h"
#include "updateImage.h"
#include "pgmHandle.h"

/*This function check the size of the pixels in the bianry file*/
char getBitSize(unsigned char reduced_gray_levels);
/*This function inserts the compressed pixel into the bit array*/
static void insertPixel(unsigned char** bitArr, unsigned char compressedPixel, int numOfBitsPerPixel, int byte, int bit);
/*This function converts the pixeles double dimensional array into bit array*/
static int compressPixels(unsigned char** bitArr, unsigned char reduced_gray_levels, grayImage* img);
/*This function prints the compressed pixels in the bitPGM*/
static void insertCompressedPixlesToFile(FILE *out_fptr, grayImage *image, unsigned char reduced_gray_levels);
/*This function creates a binary file from given grayImage*/
void saveCompressed(char* file_name, grayImage *image, unsigned char reduced_gray_levels);

#endif