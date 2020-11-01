#ifndef BIT_MAP
#define BIT_MAP

#define _CRT_SECURE_NO_WARNINGS

typedef unsigned short imgPos[2];
unsigned char* BITMAP;

/*The function creates an array of chars according to the size of image. the chars are init to 0*/
void createBitMap(unsigned short rows, unsigned short cols);
/*The function creates a mask by given position*/
static unsigned char createMaskByPos(imgPos pos, unsigned char* mask, unsigned short cols);
/*The function sets a specific bit to 1 by given position*/
void setPosToTrue(imgPos pos, unsigned short cols);
/*The function checks if a specific is 1 or zero by given position*/
char isInSegment(imgPos pos, unsigned short cols);

#endif