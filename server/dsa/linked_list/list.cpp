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

struct doubly_sentinel {
    doubly_node* sentinel;
};

doubly_node* make_doubly_list(){
    doubly_node* d = new doubly_node{};
    return d;        
}

/**
 * Makes an empty doubly linked list with sentinel
 *
 *  _________________ 
 * |                 v       
 *  \__|previous|SENTINEL|next|_
 *           ____^              |
 *          /__________________/
 *
 */
doubly_sentinel* make_doubly_ll_sent(){
    doubly_sentinel* d = new doubly_sentinel{};
    d->sentinel->satellite = NULL;
    d->sentinel->next = d->sentinel;
    d->sentinel->prev = d->sentinel;
    return d;        
}



void add_head_doubly_ll(void* satellite, doubly_sentinel* ds){
    doubly_node * node = new doubly_node();
    node->next = ds->sentinel->next;
    ds->sentinel->next->prev = node;
    node->prev = ds->sentinel;
    ds->sentinel->next = node;
}

singly_node* make_singly_list(){
    singly_node* d = new singly_node{};
    return d;        
}

singly_node* make_singly_ll_sent(){
    singly_node* d = new singly_node{};
    return d;        
}
