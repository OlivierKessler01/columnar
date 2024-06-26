#pragma once

#include <sys/types.h>

typedef struct state {
    char name[20];
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
    state* start_state;
    delta* delta_set; // Transition functions
    int delta_set_len;
    state* accepting_state;
    state* error_state;
} nfa;

typedef struct dfa {
    state* start_state;
    delta* delta_set; // Transition functions
    int delta_set_len;
    state* accepting_states;
    int accepting_states_len;
    state* error_state;
} dfa;

enum synthactic_category{
    keyword = 0,
    whitespace = 1,
    integer = 2,
    identifier = 3,
    comment = 4,
};

typedef struct token {
    char* lexeme;
    synthactic_category category;
} token;

size_t lexe(token* tokens, char* str, ssize_t str_size);
