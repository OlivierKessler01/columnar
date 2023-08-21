
#include <vector>

typedef struct {
    int height;
    std::vector<int> data;
} Heap;

bool test_build_max_heap();

Heap build_max_heap(std::vector<int> &v);

void max_heapify(Heap* heap, int index);
