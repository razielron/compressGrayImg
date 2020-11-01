#ifndef DEBINIMG
#define DEBINIMG

#define _CRT_SECURE_NO_WARNINGS
#define ERROR_OPENING_INPUT_FILE 1
#include "segment.h"
#include "bitMap.h"
#include "updateImage.h"
#include "compressPGM.h"

/*This function converts the binary settings into PGM file*/
static void insertSettingsToPGM(FILE *out_fptr, FILE *in_fptr, unsigned short *rows, unsigned short *cols, unsigned char *grayLevels);
/*This function opens the binary and PGM files*/
static void openFiles(char *compressed_file_name, char *PGM_file_name, FILE **out_fptr, FILE **in_fptr);
/*This function decompress pixel to decimal value*/
static unsigned char getDecompressedPixel(unsigned char **compressedPixels, int numOfBitsPerPixel, int byte, int bit);
/*This function pulls the binary pixels into array*/
static void getPixelsFromBinFile(FILE *in_fptr, unsigned char** compressedPixels);
/*The function inserts pixels to PGM*/
static void insertPixelsToPGM(FILE *out_fptr, unsigned char **compressedPixels, unsigned short rows, unsigned short cols, unsigned char grayLevels);
/*The function converts compressed image to PGM*/
void convertCompressedImageToPGM(char *compressed_file_name, char *PGM_file_name);

#endif