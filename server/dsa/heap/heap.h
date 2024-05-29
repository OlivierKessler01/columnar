#include <vector>

typedef struct {
    int height;
    std::vector<int> data;
} Heap;

Heap build_max_heap(std::vector<int> &v);

void max_heapify(Heap* heap, int index);

int right_child(int index);

int left_child(int index);
