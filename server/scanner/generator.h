#pragma once

#include <sys/types.h>
#include <unordered_map> 
#include <iostream>
#include <vector>
#include <random>
#include <sstream>
#include <set>

using namespace std;



/**
 * Transition function for an NFA/DFA
 */
typedef struct {
    char input; 
    string to;
} delta;

typedef struct {
   string name;
   unordered_map<string, vector<delta>> deltas; // [to -> delta...]
   unordered_map<string, vector<delta>> epsilon_deltas; // [to -> delta...]
} state;

typedef struct nfa {
    string start;
    string accept;
    set<char> sigma; // finite alphabet used by the nfa
    unordered_map<string, state> states; // [state_uid -> state...]
} nfa;


typedef struct dfa {
    string start;
    vector<string> accept;
    unordered_map<string, vector<delta>> deltas; // [state_uid -> deltas...]
} dfa;

enum synthax_cat {
    keyword = 0,
    whitespace = 1,
    integer = 2,
    identifier = 3,
    comment = 4,
};



