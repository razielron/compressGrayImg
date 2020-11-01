#define _CRT_SECURE_NO_WARNINGS
#include "allSegments.h"

static imgPosCell* allocateCell(imgPos position) {
	imgPosCell* cell;

	cell = (imgPosCell*)malloc(sizeof(imgPosCell));
	if (!cell) {
		printf("Memory allocation error for imgPosCell\n");
		exit(1);
	}

	cell->position[0] = position[0];
	cell->position[1] = position[1];
	cell->next = NULL;
	cell->prev = NULL;

	return cell;
}

static void insertHeadCell(imgPosCell* head, imgPosCell* newHead) {
	head->prev = newHead;
	newHead->next = head;
}

static void insertMiddleCell(imgPosCell* current, imgPosCell* newCell) {
	imgPosCell* temp;

	temp = current->prev;
	temp->next = newCell;
	current->prev = newCell;
	newCell->next = current;
	newCell->prev = temp;
}


static void insertEndCell(imgPosCell* tail, imgPosCell* newCell) {
	tail->next = newCell;
	newCell->prev = tail;
}


static imgPosCell* insertSortedCell(imgPosCell *head, imgPos position) {
	imgPosCell* newCell = allocateCell(position);
	int flag = TRUE;

	if (!head) {
		return newCell;
	}

	imgPosCell* temp, *current = head, *prev = current->prev;

	while (current != NULL) {
		/*if (current col is bigger than newCell col) or (current col = newCell col and current row < newCell row)*/
		if (current->position[1] > newCell->position[1] ||
			(current->position[1] == newCell->position[1] && current->position[0] > newCell->position[0])) {
			if (flag) {
				insertHeadCell(current, newCell);
				head = newCell;
			}
			else
				insertMiddleCell(current, newCell);
			return head;
		}
		flag = FALSE;
		prev = current;
		current = current->next;
	}

	insertEndCell(prev, newCell);

	return head;
}


static void convertSegment2LinkedCells(imgPosCell** head, treeNode* root) {
	int i = 0;

	if (((*head)->position[0] != root->position[0] || (*head)->position[1] != root->position[1])) {
		*head = insertSortedCell(*head, root->position);
	}

	while (root->similar_neighbors[i]) {
		convertSegment2LinkedCells(head, root->similar_neighbors[i]);
		i++;
	}
}


static void addHeadToSegments(imgPosCell*** segments,unsigned int** segmentsSize, int* size, imgPosCell* head, unsigned int currentSegmentSize) {
	*segments = (imgPosCell**)realloc(*segments, (((*size) + 1) * sizeof(imgPosCell*)));
	if (!(segments)) {
		printf("Memory allocation error for Segments array\n");
		exit(1);
	}

	*segmentsSize = (unsigned int*)realloc(*segmentsSize, (((*size) + 1) * sizeof(unsigned int)));
	if (!(*segmentsSize)) {
		printf("Memory allocation error for Segments Size array\n");
		exit(1);
	}

	(*segments)[*size] = head;
	(*segmentsSize)[*size] = currentSegmentSize;
	(*size)++;
}

static void findMinCell(grayImage* img, imgPos* kernel, int* flag) {
	int i, j, current_min = 256;
	imgPos temp;

	(*kernel)[0] = NULL;
	(*kernel)[1] = NULL;
	*flag = 0;

	for (i = 0; i < img->rows; i++) {
		for (j = 0; j < img->cols; j++) {
			temp[0] = i;
			temp[1] = j;

			if (!(isInSegment(temp, img->cols)) && img->pixels[i][j] < current_min) {
				(*kernel)[0] = i;
				(*kernel)[1] = j;
				*flag = 1;
				current_min = img->pixels[i][j];
			}
		}
	}
}

static void swap(unsigned int* s1, unsigned int* s2, imgPosCell** ipc1, imgPosCell** ipc2) {
	unsigned int tempS;
	imgPosCell* tempIpc;

	tempS = *s2;
	*s2 = *s1;
	*s1 = tempS;

	tempIpc = *ipc2;
	*ipc2 = *ipc1;
	*ipc1 = tempIpc;
}


static void bubbleSortSegmentsDesc(imgPosCell*** segments, unsigned int** segmentsSize, int size) {
	int i, j;

	for (i = 0; i < size - 1; i++)
		for (j = 0; j < size - i - 1; j++)
			if ((*segmentsSize)[j] < (*segmentsSize)[j + 1])
				swap((*segmentsSize) + j, (*segmentsSize) + j + 1, (*segments) + j, (*segments) + j + 1);
}


unsigned int findAllSegments(grayImage* img, unsigned char threshold, imgPosCell*** segments) {
	int size = 0, flag;
	imgPos kernel;
	Segment* segment = NULL;
	unsigned int* segmentsSize;
	imgPosCell* head = NULL;

	createBitMap(img->rows, img->cols);

	*segments = (imgPosCell**)malloc(sizeof(imgPosCell*));
	if (!(*segments)) {
		printf("Memory allocation error\n");
		exit(1);
	}

	segmentsSize = (unsigned int*)calloc(1, sizeof(unsigned int));
	if (!segmentsSize) {
		printf("Memory allocation error\n");
		exit(1);
	}

	findMinCell(img, &kernel, &flag);

	while (flag) {
		segment = findSingleSegment(img, kernel, threshold);
		head = insertSortedCell(head, segment->root->position);
		convertSegment2LinkedCells(&head, segment->root);
		addHeadToSegments(segments,&segmentsSize, &size, head, segment->size);
		findMinCell(img, &kernel, &flag);
		freeTree(segment->root);
		free(segment);
		head = NULL;
	}

	bubbleSortSegmentsDesc(segments, &segmentsSize, size);
	free(segmentsSize);
	free(BITMAP);

	return size;
}
