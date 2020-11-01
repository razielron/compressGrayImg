#define _CRT_SECURE_NO_WARNINGS
#define ERROR_OPENING_INPUT_FILE 1
#include "updateImage.h"

static void updateSegment(grayImage *img, imgPosCell *segment, unsigned int size, unsigned int segmentNum) {
	int i;
	while (segment) {
		img->pixels[segment->position[0]][segment->position[1]] = segmentNum * (255 / (size - 1));
		segment = segment->next;
	}
}

grayImage *colorSegments(grayImage *img, imgPosCell **segments, unsigned int size) {
	unsigned int i;
	for (i = 0; i < size; i++)
		updateSegment(img, segments[i], size, i);
	return img;
}