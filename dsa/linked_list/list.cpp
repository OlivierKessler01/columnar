#include <math.h>
#include <cassert>
#include <vector>
#include <iostream>
#include <stdexcept>
#include "../vector_utils.h"

struct singly_node {
    void* satellite;
    singly_node* next;
};

struct doubly_node {
    void* satellite;
    doubly_node* next;
    doubly_node* prev;
};


doubly_node make_doubly_list(){
    doubly_node d = doubly_node{};
    return d;        
}

doubly_node make_doubly_list_sentinel(){
    doubly_node d = doubly_node{};
    return d;        
}

singly_node make_singly_list(){
    singly_node d = singly_node{};
    return d;        
}

singly_node make_singly_list_sentinel(){
    singly_node d = singly_node{};
    return d;        
}
