#ifndef SEGMENT
#define SEGMENT

#define PI 2

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitMap.h"

#define TRUE    1
#define FALSE   0
#define ILLEGAL_OPERATOR   -1
#define MEMORY_ALLOCATING_ERROR -1


typedef struct _grayImage {
	unsigned short rows, cols;
	unsigned char** pixels;
}grayImage;

typedef struct _treeNode {
	imgPos position;
	struct _treeNode** similar_neighbors;
}treeNode;

typedef struct _segment {
	treeNode* root;
	unsigned int size;
}Segment;

/*This Function free the memory of the tree*/
void freeTree(treeNode* root);
/*The function creates new segment*/
static Segment* AllocateSegment(treeNode* node);
/*The function creates new Tree Node*/
static treeNode* AllocateTreeNode(imgPos pos);
/*The function insert a tree node to similar neighbor array of father*/
static void InsertChildNode(treeNode* father, treeNode* child);
/*The function checks if the neighbor has a valid value and a valid position*/
static unsigned char validNeighbor(grayImage *img, imgPos cell, imgPos kernel, unsigned char posThresh, unsigned char negThresh);
/*The function returns the size of the array given*/
static int getArrSize(treeNode** arr);
/*The function creates a segment by sorting all neighbors with threshold*/
static void singleSegmentReq(grayImage* img, imgPos kernel, unsigned char posThresh, unsigned char negThresh, treeNode* father, unsigned int* size);
/*The function find a segment for given kernel*/
Segment* findSingleSegment(grayImage* img, imgPos kernel, unsigned char threshold);

#endif