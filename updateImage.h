#ifndef UPDATEIMAGE
#define UPDATEIMAGE

#define _CRT_SECURE_NO_WARNINGS
#define ERROR_OPENING_INPUT_FILE 1

#include <string.h>
#include "allSegments.h"
#include "segment.h"
#include "bitMap.h"


/*The function updates the pixel value*/
static void updateSegment(grayImage *img, imgPosCell *segment, unsigned int size, unsigned int segmentNum);
/*The function updates the greyImage values*/
grayImage *colorSegments(grayImage *img, imgPosCell **segments, unsigned int size);

#endif