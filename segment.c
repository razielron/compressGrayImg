#define _CRT_SECURE_NO_WARNINGS
#include "segment.h"

void freeTree(treeNode* root) {
	int i = 0;

	while (root->similar_neighbors[i]) {
		freeTree(root->similar_neighbors[i]);
		i++;
	}

	free(root->similar_neighbors);
	free(root);
}

static Segment* AllocateSegment(treeNode* node) {
	Segment* segment;
	treeNode* root;

	segment = (Segment*)malloc(sizeof(Segment));
	if (segment == NULL) {
		printf("segment malloc didn't work");
		exit(1);
	}

	root = (Segment*)malloc(sizeof(Segment));
	if (root == NULL) {
		printf("root malloc didn't work");
		exit(1);
	}

	segment->root = node;
	segment->size = 1;
}

static treeNode* AllocateTreeNode(imgPos pos) {
	treeNode* node;
	treeNode** similar_neighbors;

	node = (treeNode*)malloc(sizeof(treeNode));
	if (node == NULL) {
		printf("node malloc didn't work");
		exit(1);
	}

	node->similar_neighbors = (treeNode**)malloc(sizeof(treeNode*));
	if (node->similar_neighbors == NULL) {
		printf("node->similar_neighbors malloc didn't work");
		exit(1);
	}

	node->similar_neighbors[0] = NULL;
	node->position[0] = pos[0];
	node->position[1] = pos[1];

	return node;
}

static int getArrSize(treeNode** arr) {
	int i = 0;
	while ((arr)[i] != NULL) {
		i++;
	}
	return i + 1;

}

static void InsertChildNode(treeNode* father, treeNode* child) {

	int size = getArrSize(father->similar_neighbors);

	father->similar_neighbors = (treeNode**)realloc(father->similar_neighbors, (size + 1) * sizeof(treeNode*));
	if (father->similar_neighbors == NULL) {
		printf("realloc didn't work");
		exit(1);
	}

	father->similar_neighbors[size - 1] = child;
	father->similar_neighbors[size] = NULL;
}

static void singleSegmentReq(grayImage* img, imgPos kernel, unsigned char posThresh, unsigned char negThresh, treeNode* father, unsigned int* size) {
	imgPos neighbor;
	treeNode* neighborChild;
	unsigned char kernelValue = img->pixels[kernel[0]][kernel[1]];
	unsigned char neighborValue;
	int i, row, col;

	for (i = 0; i < 8; i++) {
		switch (i) {
		case 0:
			row = col = -1;
			break;
		case 1:
			row = -1;
			col = 0;
			break;
		case 2:
			row = -1;
			col = 1;
			break;
		case 3:
			row = 0;
			col = 1;
			break;
		case 4:
			row = col = 1;
			break;
		case 5:
			row = 1;
			col = 0;
			break;
		case 6:
			row = 1;
			col = -1;
			break;
		case 7:
			row = 0;
			col = -1;
			break;
		}

		neighbor[0] = kernel[0] + row;
		neighbor[1] = kernel[1] + col;

		if (validNeighbor(img, neighbor, kernel, posThresh, negThresh) && !(isInSegment(neighbor, img->cols))) {
			setPosToTrue(neighbor, img->cols);
			neighborChild = AllocateTreeNode(neighbor);
			InsertChildNode(father, neighborChild);
			neighborValue = img->pixels[neighbor[0]][neighbor[1]];
			(*size)++;
			singleSegmentReq(img, neighbor, posThresh + (kernelValue - neighborValue), negThresh - (kernelValue - neighborValue), neighborChild, size);
		}
	}
}

static unsigned char validNeighbor(grayImage *img, imgPos cell, imgPos kernel, unsigned char posThresh, unsigned char negThresh) {

	if (cell[0] < 0 || cell[0] >= img->rows || cell[1] < 0 || cell[1] >= img->cols) {
		return 0;
	}

	unsigned char cellValue = img->pixels[cell[0]][cell[1]];
	unsigned char kernelValue = img->pixels[kernel[0]][kernel[1]];

	if (cellValue < (kernelValue - negThresh) || cellValue >(kernelValue + posThresh)) {
		return 0;
	}

	return 1;
}

/*Q1*/
Segment* findSingleSegment(grayImage* img, imgPos kernel, unsigned char threshold) {
	treeNode* root;
	Segment* segment;
	char bitMapFlag = 0;

	if (!BITMAP) {
		bitMapFlag = 1;
		createBitMap(img->rows, img->cols);
	}

	root = AllocateTreeNode(kernel);
	segment = AllocateSegment(root);
	setPosToTrue(kernel, img->cols);
	singleSegmentReq(img, kernel, threshold, threshold, root, &(segment->size));
	return segment;

	if (bitMapFlag) {
		free(BITMAP);
	}
}