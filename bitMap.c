#define _CRT_SECURE_NO_WARNINGS
#include "bitMap.h"

void createBitMap(unsigned short rows, unsigned short cols) {
	int size = (((cols * rows) / 8) + 1);
	BITMAP = (unsigned char*)calloc(size, sizeof(char));

	if (!BITMAP) {
		printf("bitMap malloc didn't work");
		exit(1);
	}
}


static unsigned char createMaskByPos(imgPos pos, unsigned char* mask, unsigned short cols) {
	int flatPos = (pos[0] * cols) + pos[1];
	int index = (flatPos / 8);
	int rest = flatPos % 8;
	*mask <<= (7 - rest);
	return index;
}

void setPosToTrue(imgPos pos, unsigned short cols) {
	int index;
	unsigned char* mask = (unsigned char*)malloc(sizeof(unsigned char));

	if (!mask) {
		printf("bitMap malloc didn't work");
		exit(1);
	}

	*mask = 1;
	index = createMaskByPos(pos, mask, cols);
	BITMAP[index] |= *mask;
	free(mask);
}

char isInSegment(imgPos pos, unsigned short cols) {
	int index, bool;
	unsigned char* mask = (unsigned char*)malloc(sizeof(unsigned char));

	if (!mask) {
		printf("bitMap malloc didn't work");
		exit(1);
	}

	*mask = 1;
	index = createMaskByPos(pos, mask, cols);
	bool = (BITMAP[index] & *mask);
	free(mask);
	return bool;
}