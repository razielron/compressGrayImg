#define _CRT_SECURE_NO_WARNINGS
#define ERROR_OPENING_INPUT_FILE 1
#include "decompressBinaryImage.h"

static void insertSettingsToPGM(FILE *out_fptr, FILE *in_fptr, unsigned short *rows, unsigned short *cols, unsigned char *grayLevels) {

	fread(cols, sizeof(unsigned short), 1, in_fptr);
	fread(rows, sizeof(unsigned short), 1, in_fptr);
	fread(grayLevels, sizeof(unsigned char), 1, in_fptr);

	fprintf(out_fptr, "P2\n%hu %hu\n%hhu\n", *cols, *rows, 255);
}

static void openFiles(char *compressed_file_name, char *PGM_file_name, FILE **out_fptr, FILE **in_fptr) {

	*in_fptr = fopen(compressed_file_name, "rb");
	if (*in_fptr == NULL) {
		fprintf(stderr, "Error opening input file %s\n", compressed_file_name);
		exit(ERROR_OPENING_INPUT_FILE);
	}
	
	*out_fptr = fopen(PGM_file_name, "w");
	if (*out_fptr == NULL) {
		fprintf(stderr, "Error opening input file %s\n", PGM_file_name);
		exit(ERROR_OPENING_INPUT_FILE);
	}
}

static unsigned char getDecompressedPixel(unsigned char **compressedPixels, int numOfBitsPerPixel, int byte, int bit) {
	unsigned char pixel = 0;
	if (bit <= (8 - numOfBitsPerPixel)) {
		pixel = ((*compressedPixels)[byte]) >> (8 - numOfBitsPerPixel - bit);
	}
	else{
		pixel = (((*compressedPixels)[byte]) << (bit)) >> (8 - numOfBitsPerPixel);
		pixel |= ((*compressedPixels)[byte + 1]) >> (16 - bit - numOfBitsPerPixel);
	}
	return pixel;
}

static void getPixelsFromBinFile(FILE *in_fptr,unsigned char** compressedPixels) {
	int arrSize = 0;

	while (!feof(in_fptr)) {
		arrSize++;
		(*compressedPixels) = (unsigned char*)realloc((*compressedPixels), (sizeof(unsigned char)*arrSize));
		if (!(*compressedPixels)) {
			printf("Memory reallocation error\n");
			exit(1);
		}
		fread(((*compressedPixels) + (arrSize - 1)), sizeof(unsigned char), 1, in_fptr);
	}
}

static void insertPixelsToPGM(FILE *out_fptr,unsigned char **compressedPixels, unsigned short rows, unsigned short cols, unsigned char grayLevels) {
	int i, j, pixelNumber=0;
	int numOfBitsPerPixel = getBitSize(grayLevels);
	unsigned char decompressedPixel;

	for (i = 0;i < rows;i++) {
		for (j = 0;j < cols;j++) {
			pixelNumber++;
			decompressedPixel = getDecompressedPixel(compressedPixels,
				numOfBitsPerPixel,
				((pixelNumber - 1)*numOfBitsPerPixel / 8),
				((pixelNumber - 1)*numOfBitsPerPixel % 8));
			fprintf(out_fptr, "%hhu", ((decompressedPixel*256/grayLevels) + (256/grayLevels - 1)));
			if (j < cols - 1)
				fprintf(out_fptr, " ");
		}
		if (i < rows - 1)
			fprintf(out_fptr, "\n");
	}
}

void convertCompressedImageToPGM(char *compressed_file_name, char *PGM_file_name) {
	FILE *out_fptr = NULL, *in_fptr = NULL;
	char *compressedPixels = NULL;
	unsigned short rows, cols;
	char grayLevels;

	openFiles(compressed_file_name, PGM_file_name, &out_fptr, &in_fptr);
	insertSettingsToPGM(out_fptr, in_fptr, &rows, &cols, &grayLevels);
	getPixelsFromBinFile(in_fptr, &compressedPixels);
	insertPixelsToPGM(out_fptr, &compressedPixels, rows, cols, grayLevels);
	free(compressedPixels);
	fclose(in_fptr);
	fclose(out_fptr);
}
