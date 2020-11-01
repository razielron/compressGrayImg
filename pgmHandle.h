#ifndef PGMHANDLE
#define PGMHANDLE

#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include "allSegments.h"
#include "segment.h"
#include "bitMap.h"
#include "updateImage.h"

/*This function allocates grayImage*/
static grayImage* allocateGrayImage(unsigned short rows, unsigned short cols);
/*This function check if the file is from P2 type*/
static void checkIfP2(FILE *in_fptr);
/*This function gets the fptr in a new line*/
static void getNewLine(FILE *in_fptr);
/*This function gets the rows and cols from the file and alloctes&returns grayImage*/
static grayImage* createGrayImageByFile(FILE *in_fptr);
/*This function skips comments*/
static void skipComments(FILE *in_fptr);
/*This function read the pixels from given file and insert them into a given grayImage*/
static void insertGrayLevelsByFile(FILE *in_fptr, grayImage* image);
/*This function reads a file and creates grayImage*/
grayImage *readPGM(char *fname);

#endif
