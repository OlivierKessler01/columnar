#pragma once

#include <sys/types.h>
#include <unordered_map> 
#include <iostream>
#include <vector>
#include <random>
#include <sstream>

using namespace std;



/**
 * Transition function for an NFA/DFA
 */
struct delta {
    string from;
    union {
        char input; 
        bool epsilon;
    };
    string to;
};

typedef struct nfa {
    string start;
    string accept;
    unordered_map<string, vector<delta>> deltas; // [state_uid -> deltas...]
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

typedef struct token {
    char* lexeme;
    synthax_cat category;
} token;

size_t lexe(token* tokens, char* str, ssize_t str_size);
