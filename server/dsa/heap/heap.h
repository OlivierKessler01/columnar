#include <vector>

typedef struct {
    int height;
    std::vector<int> data;
} Heap;

Heap build_max_heap(std::vector<int> &v);
