#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "heap.h"
#include "util.h"

extern VERTEX* V;

void freeHeap(HEAP* heap) {
	free(heap->H);
	free(heap);
}

int Insert(HEAP* heap, ELEMENT* element) {

	if (heap->size >= heap->capacity) {
		printf("Problem in Insert: Heap full...\n");
		return 1;
	}

	heap->size++;
	heap->H[heap->size] = element;
	V[heap->H[heap->size]->vertex].pos = heap->size;
	MovingUp(heap, heap->size);
	return 0;
}

void MovingUp(HEAP* heap, int pos) {

	pElement temp;
	int parent;

	parent = pos / 2;
	if (pos > 1 && heap->H[pos]->key < heap->H[parent]->key) {
		temp = heap->H[pos];
		heap->H[pos] = heap->H[parent];
		heap->H[parent] = temp;
		V[heap->H[pos]->vertex].pos = pos;
		V[heap->H[parent]->vertex].pos = parent;
		MovingUp(heap, parent);
	}
}
	
int decreaseKey(HEAP* heap, int pos, float newKey) {
	if (pos ==0 || pos >heap->size || newKey >= heap->H[pos]->key) {
		return 1;
	}

	heap->H[pos]->key = newKey;
	MovingUp(heap, pos);
	return 0;
}

HEAP* heapInit(int capacity) {
	HEAP* heap =new HEAP;
	heap->capacity = capacity;
	heap->size = 0;

	heap->H = new pElement[capacity+1];

	return heap;	
}	

pElement extractMin(HEAP* heap, int flag) {
	
	pElement min, last;

	if (heap->size < 1) {
		printf("Error: Heap is empty");
		return NULL;
	}
	else {
	
		min = heap->H[1];
		last=heap->H[heap->size--];
		heap->H[1] = last;
		V[heap->H[1]->vertex].pos = 1;
		V[min->vertex].pos = 0;
		

		minHeapify(heap, 1);
		return min;
	}
	return NULL;
}

HEAP* minHeapify(HEAP* heap, int index) {

	int smallest, left, right;
	smallest = index;
	left = 2 * index + 1;
	right = 2 * index + 2;

	if (left <= heap->size && heap->H[left]->key < heap->H[index]->key) {
		smallest = left;
	}

	if (right <= heap->size && heap->H[right]->key < heap->H[index]->key) {
		smallest = right;
	}

	if (smallest != index) {
		pElement smallestElement = heap->H[smallest];
		pElement indexElement = heap->H[index];

		V[smallestElement->vertex].pos = index;
		V[indexElement->vertex].pos = smallest;

		pElement temp = smallestElement;
		smallestElement = indexElement;
		indexElement = temp;

		minHeapify(heap, smallest);

	}
	return heap;
}


