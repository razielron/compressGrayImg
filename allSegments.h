#ifndef ALL_SEGMENTS
#define ALL_SEGMENTS

#define _CRT_SECURE_NO_WARNINGS
#include "segment.h"
#include <string.h>

typedef struct _imgPosCell {
	imgPos position;
	struct _imgPosCell* next, *prev;
}imgPosCell;

/*The function creates a new cell with given position*/
static imgPosCell* allocateCell(imgPos position);
/*The function insert a cell in between 2 cells in the Head*/
static void insertHeadCell(imgPosCell* head, imgPosCell* newHead);
/*The function insert a cell in between 2 cells in the middle*/
static void insertMiddleCell(imgPosCell* current, imgPosCell* newCell);
/*The function insert new cell into the end of the list*/
static void insertEndCell(imgPosCell* tail, imgPosCell* newCell);
/*The function inserts a new cell (by it's position) to existed list in a sorted way (navigation)*/
static imgPosCell* insertSortedCell(imgPosCell* head, imgPos position);
/*The function goes over Segment tree, creates Linked list of Cells and returns the Head*/
static void convertSegment2LinkedCells(imgPosCell** head, treeNode* root);
/*The function insert given head to the given segments array*/
static void addHeadToSegments(imgPosCell*** segments, unsigned int** segmentsSize, int* size, imgPosCell* head, unsigned int currentSegmentSize);
/*The function finds the current min position in Img by the threshold bottomRange*/
static void findMinCell(grayImage* img, imgPos *kernel, int* flag);
/*This function swaps cells*/
static void swap(unsigned int* s1, unsigned int* s2, imgPosCell** ipc1, imgPosCell** ipc2);
/*This function makes descending sort by segment size of the grayImage*/
static void bubbleSortSegmentsDesc(imgPosCell*** segments, unsigned int** segmentsSize, int size);
/*This function finds all the segments and arrange them in array*/
unsigned int findAllSegments(grayImage* img, unsigned char threshold, imgPosCell*** segments);

#endif