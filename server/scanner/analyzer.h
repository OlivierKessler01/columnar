#pragma once

#include <sys/types.h>

typedef struct state {
    char name[200];
} state;

/**
 * Transition function for an NFA/DFA
 */
typedef struct delta {
    state* start_state;
    union {
        char input; 
        bool epsilon;
    };
    state* end_state;
} delta;

typedef struct nfa {
    delta* delta_set; // Transition functions
    int delta_set_len;
    state* state_set; //Sets that aren't start or accepting or error
                      // [0] is start start
                      // [1] is accepting state
    int state_set_len;
} nfa;

typedef struct dfa {
    state* start_state;
    delta* delta_set; // Transition functions
    int delta_set_len;
    state* accepting_states;
    int accepting_states_len;
    state* error_state;
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
