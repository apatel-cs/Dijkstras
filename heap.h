#pragma once

typedef struct TAG_ELEMENT { 
	float key; 
	int vertex;
}ELEMENT; 

typedef ELEMENT* pElement;
typedef struct TAG_HEAP { 
	int capacity;  /* max size of the heap */
	int size;      /* current size of the heap */
	pElement* H;/* pointer to pointers to elements */ 

}HEAP;

void MovingUp(HEAP* heap, int pos);
void freeHeap(HEAP* heap);
int Insert(HEAP* heap, ELEMENT* element);
int decreaseKey(HEAP* heap, int pos, float newkey);
HEAP* heapInit(int capacity);
pElement extractMin(HEAP* heap, int flag);
HEAP* minHeapify(HEAP* heap, int index);
