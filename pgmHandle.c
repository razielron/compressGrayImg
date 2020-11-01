#define _CRT_SECURE_NO_WARNINGS
#define ERROR_OPENING_INPUT_FILE 1

#include "pgmHandle.h"

static grayImage* allocateGrayImage(unsigned short rows, unsigned short cols) {
	grayImage* image;
	int i;

	image = (grayImage*)malloc(sizeof(grayImage));
	if (image == NULL) {
		printf("image malloc didn't work");
		exit(1);
	}

	image->cols = cols;
	image->rows = rows;
	image->pixels = (unsigned char**)malloc(sizeof(unsigned char*) * rows);

	if (image->pixels == NULL) {
		printf("image malloc didn't work");
		exit(1);
	}

	for (int i = 0; i < image->rows; i++) {
		image->pixels[i] = (unsigned char*)malloc((sizeof(unsigned char)*cols));
		if (image->pixels[i] == NULL) {
			printf("image malloc didn't work");
			exit(1);
		}
	}

	return image;
}

static void checkIfP2(FILE *in_fptr) {
	if (getc(in_fptr) != 'P' || getc(in_fptr) != '2') {
		fprintf(stderr, "Error file type\n");
		exit(ERROR_OPENING_INPUT_FILE);
	}
}

static void getNewLine(FILE *in_fptr) {
	char c;
	while ((c = getc(in_fptr)) != '\n') {
		if (c == EOF) {
			fprintf(stderr, "Error: no new line\n");
			exit(ERROR_OPENING_INPUT_FILE);
		}
	}
}

static grayImage* createGrayImageByFile(FILE *in_fptr) {
	int rows = 0, cols = 0;

	if (!feof(in_fptr)) {
		fscanf(in_fptr, "%d", &cols);
	}

	if (!feof(in_fptr)) {
		fscanf(in_fptr, "%d", &rows);
	}

	return allocateGrayImage(rows, cols);
}

static void skipComments(FILE *in_fptr) {
	char c;
	while ((c = getc(in_fptr)) == '#') {
		getNewLine(in_fptr);
	}
	if (c == EOF) {
		fprintf(stderr, "Error: no new line\n");
		exit(ERROR_OPENING_INPUT_FILE);
	}
	fseek(in_fptr, -1L, SEEK_CUR);
}

static void insertGrayLevelsByFile(FILE *in_fptr, grayImage* image) {
	int i, j;
	int c = 0;

	for (i = 0;i < image->rows;i++) {
		for (j = 0; j < image->cols;j++) {
			if (!feof(in_fptr)) {
				fscanf(in_fptr, "%d", &c);
				image->pixels[i][j] = c;
			}
			else {
				fprintf(stderr, "Error in file - not enough values in IMG\n");
				exit(ERROR_OPENING_INPUT_FILE);
			}
		}
	}
}


grayImage *readPGM(char *fname) {
	grayImage* image;
	FILE *in_fptr;


	in_fptr = fopen(fname, "r");
	if (in_fptr == NULL) {
		fprintf(stderr, "Error opening input file %s\n", fname);
		exit(ERROR_OPENING_INPUT_FILE);
	}

	checkIfP2(in_fptr);
	getNewLine(in_fptr);
	skipComments(in_fptr);
	image = createGrayImageByFile(in_fptr);
	insertGrayLevelsByFile(in_fptr, image);
	fclose(in_fptr);
	return image;
}
