#include<stdlib.h>
#include<stdio.h>
#include "graph.h"
#include "heap.h"
#include "util.h"

extern VERTEX* V;

void printPath(int n, int source, int destination, int s, int t) {

	PATH* pPATH;
	PATH* pNODE;

	int u, v;

	if (V[t].color == 0) {
		if (destination < 1 || destination > n || t == destination) {
			printf("No %d-%d path exists.\n", s, t);
			return;
		} else {
			printf("No %d-%d path has been computed.\n", s, t);
			return;
		}
	} else if (V[t].color == 1) {
		printf("Path not known to be shortest: <%d", s);

	} else if (V[t].color == 2) {
		printf("Shortest path: <%d", s);
	}

	pNODE = (PATH*)malloc(sizeof(PATH));
	pNODE->vertex = t;
	pNODE->next = NULL;
	pPATH = pNODE;
	v = pNODE->vertex;

	while (V[v].pi) {
		u = V[v].pi;
		pNODE = (PATH*)malloc(sizeof(PATH));
		pNODE->vertex = u;
		pNODE->next = pPATH;
		pPATH = pNODE;
		v = pNODE->vertex;
	}

	pNODE = pPATH;
	pPATH = pPATH->next;
	free(pNODE);

	while (pPATH) {
		pNODE = pPATH;
		printf(", %d", pNODE->vertex);
		pPATH = pPATH->next;
		free(pNODE);
	}
	printf(">\n");
	printf("The path weight is: %12.4f\n", V[t].dist);
}

void dijkstra(int n, pNODE* A, int s, int t, int flag) {
	
	pNODE node;
	HEAP* heap;
	ELEMENT* element;

	int u, v, i;
	float w;

	int pos;

	for (i = 1; i <= n; i++) {
		V[i].color = 0;
		V[i].pi = 0;
	}

	V[s].dist = 0;
	V[s].color = 1;

	heap = heapInit(n);
	element = (ELEMENT*)malloc(sizeof(ELEMENT));
	element->vertex = s;
	element->key = 0;
	Insert(heap, element);

	if (flag == 1) {
		printf("Insert vertex %d, key=%12.4f\n", element->vertex, element->key);
	}

	while (heap->size) {
		element = extractMin(heap, flag);
		if (flag == 1) {
			printf("Delete vertex %d, key=%12.4f\n", element->vertex, element->key);
		}

		u = element->vertex;
		V[u].color = 2;
		if (element->vertex == t) {
			break;
		}
		free(element);

		node = A[u];
		while (node) {
			v = node->v;
			w = node->w;
			if (V[v].color == 0) {
				V[v].dist= V[u].dist + w;
				V[v].pi = u;
				V[v].color = 1;
				V[v].pos = heap->size + 1;
				element = (ELEMENT*)malloc(sizeof(ELEMENT));
				element->vertex = v;
				element->key = V[v].dist;
				Insert(heap, element);
				if (flag == 1) {
					printf("Insert vertex %d, key=%12.4f\n", element->vertex, element->key);
				}
			}
			else if (V[v].dist > V[u].dist + w) {
				if (flag == 1) {
					printf("Decrease key of vertex %d, from %12.4f to %12.4f\n", v, V[v].dist, V[u].dist + w);
				}
				V[v].dist = V[u].dist + w;
				V[v].pi = u;
				pos = V[v].pos;
				decreaseKey(heap, pos, V[v].dist);
			}

			node = node->next;
		}
		
	}
	freeHeap(heap);
}