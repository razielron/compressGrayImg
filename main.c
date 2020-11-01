#define _CRT_SECURE_NO_WARNINGS

#include "segment.h"
#include "allSegments.h"
#include "updateImage.h"
#include "pgmHandle.h"
#include "compressPGM.h"
#include "decompressBinaryImage.h"

void runReadPGM(char* fname, grayImage** img);
void runFindAllSegments(grayImage* img, unsigned int threshold, imgPosCell*** segments, unsigned int* segmentsSize);
void runColorSegments(grayImage* img, imgPosCell** segments, unsigned int segmentsSize, grayImage** coloredImg);
void runSaveCompressed(char* fname, grayImage* coloredImg, unsigned char reduced_gray_levels);
void runDecompress(char* in_fname, char* out_fname);
void test();


void main()
{
	test();
}

void test() {
	unsigned int segmentsSize;
	grayImage* img, * coloredImg;
	imgPosCell** segments;

	runReadPGM("init.pgm", &img);
	runFindAllSegments(img, 10, &segments, &segmentsSize);
	runColorSegments(img, segments, segmentsSize, &coloredImg);
	runSaveCompressed("init-compressed.bin", coloredImg, 32);
	runDecompress("init-compressed.bin", "init-decompressed.pgm");
}

void runReadPGM(char* fname, grayImage** img) {
	printf("Read PGM Started...\n");
	*img = readPGM(fname);
	printf("Read PGM Finished!\n\n");
}

void runFindAllSegments(grayImage* img, unsigned int threshold, imgPosCell*** segments, unsigned int* segmentsSize) {
	printf("Find All Segments Started...\n");
	*segmentsSize = findAllSegments(img, threshold, segments);
	printf("Find All Segments Finished!\n\n");
}

void runColorSegments(grayImage* img, imgPosCell** segments, unsigned int segmentsSize, grayImage** coloredImg) {
	printf("Color Segments Started...\n");
	*coloredImg = colorSegments(img, segments, segmentsSize);
	printf("Color Segments Finished!\n\n");
}

void runSaveCompressed(char* fname, grayImage* coloredImg, unsigned char reduced_gray_levels) {
	printf("Save Compressed Started...\n");
	saveCompressed(fname, coloredImg, reduced_gray_levels);
	printf("Save Compressed Finished!\n\n");
}

void runDecompress(char* in_fname, char* out_fname) {
	printf("Save Compressed Started...\n");
	convertCompressedImageToPGM(in_fname, out_fname);
	printf("Save Compressed Finished!\n\n");
}