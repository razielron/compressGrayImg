#define _CRT_SECURE_NO_WARNINGS
#define ERROR_OPENING_INPUT_FILE 1
#include "compressPGM.h"

char getBitSize(unsigned char reduced_gray_levels) {
	int counter = 0;
	unsigned char mask = 1;
	while (!(mask & reduced_gray_levels)) {
		mask <<= 1;
		counter++;
	}
	return counter;
}

static void insertPixel(unsigned char** bitArr, unsigned char compressedPixel, int numOfBitsPerPixel, int byte, int bit) {
	if (bit <= 8 - numOfBitsPerPixel)
		(*bitArr)[byte] |= (compressedPixel << (8 - numOfBitsPerPixel - bit));
	else
	{
		(*bitArr)[byte] |= (compressedPixel >> (bit - 8 + numOfBitsPerPixel));
		(*bitArr)[byte + 1] |= (compressedPixel << (16 - numOfBitsPerPixel - bit));
	}
}

static int compressPixels(unsigned char **bitArr, unsigned char reduced_gray_levels, grayImage *img) {
	int i, j, numOfBits, pixelNumber = 0, numOfBitsPerPixel, arrSize;
	unsigned char* bitArrTemp;

	numOfBitsPerPixel = getBitSize(reduced_gray_levels);
	numOfBits = (img->cols)*(img->rows)*numOfBitsPerPixel;
	arrSize = (numOfBits % 8) ? ((numOfBits / 8) + 1) : (numOfBits / 8);

	*bitArr = (unsigned char*)calloc(arrSize, sizeof(unsigned char));
	if (!(*bitArr)) {
		printf("Memory allocation error for imgPosCell\n");
		exit(1);
	}

	for (i = 0;i < img->rows;i++) {
		for (j = 0;j < img->cols;j++) {
			pixelNumber++;
			insertPixel(bitArr,
				((img->pixels[i][j]) * reduced_gray_levels / 256),
				numOfBitsPerPixel,
				((pixelNumber - 1)*numOfBitsPerPixel) / 8,
				((pixelNumber - 1)*numOfBitsPerPixel) % 8);
		}
	}
	return arrSize;
}

static void insertCompressedPixlesToFile(FILE *out_fptr, grayImage *image, unsigned char reduced_gray_levels) {
	int i = 0, arrSize;
	unsigned char* bitArr;

	arrSize = compressPixels(&bitArr, reduced_gray_levels, image);

	fwrite(bitArr, sizeof(unsigned char), arrSize, out_fptr);

	free(bitArr);
}

void saveCompressed(char* file_name, grayImage *image, unsigned char reduced_gray_levels) {
	FILE *out_fptr;

	out_fptr = fopen(file_name, "wb");
	if (out_fptr == NULL) {
		fprintf(stderr, "Error opening input file %s\n", file_name);
		exit(ERROR_OPENING_INPUT_FILE);
	}

	fwrite(&(image->cols), sizeof(unsigned short), 1, out_fptr);
	fwrite(&(image->rows), sizeof(unsigned short), 1, out_fptr);
	fwrite(&reduced_gray_levels, sizeof(unsigned char), 1, out_fptr);
	insertCompressedPixlesToFile(out_fptr, image, reduced_gray_levels);
	fclose(out_fptr);
}
