/**
 * HEAP datastructure
 * Materialized as a vector
 */

#include <stdio.h>
#include <math.h>
#include <stdio.h>

typedef struct {
    int height;
    int n;
    std::vector<int> * data;
} Heap;

Heap* initialize() {
    Heap heap;
    heap.height = 0;
    heap.data = NULL;
    return &heap;
}

Heap* heapify(Heap* heap) {
}

bool save_on_disk(Heap*, FILE * fd) {
    return false;
}

Heap* load_from_disk(FILE *fd) {
    Heap heap; 
    return &heap;
}

int parent(int index) {
    return floor(static_cast<double>(i) / 2);
}

int right_child(int index) {
    return 2*index;
}

int left_child(int index) {
    return 2*index + 1;
}
