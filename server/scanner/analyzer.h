#pragma once

#include <sys/types.h>
#include <unordered_map> 
#include <iostream>
#include <vector>

using namespace std;


/**
 * Transition function for an NFA/DFA
 */
typedef struct delta {
    string start_state;
    union {
        char input; 
        bool epsilon;
    };
    string end_state;
} delta;

typedef struct nfa {
    string start;
    string accept;
    unordered_map<string, vector<delta>> delta_inorder; // [state_uid -> deltas...]
    unordered_map<string, vector<delta>> delta_inverse; // [state_uid -> delta...]
} nfa;

typedef struct dfa {
    string start;
    vector<string> accept;
    unordered_map<string, vector<delta>> delta_inorder; // [state_uid -> deltas...]
    unordered_map<string, vector<delta>> delta_inverse; // [state_uid -> delta...]
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
