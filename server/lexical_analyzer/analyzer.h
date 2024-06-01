#pragma once

typedef struct state {
    char name[20];
} state;

/**
 * Transition function for an NFA/DFA
 */
typedef struct delta {
    state start_state;
    state end_state;
} delta;

typedef struct nfa {
    state start_state;
    delta* delta; // Transition functions
    int delta_len;
    state accepting_state;
    state error_state;
} nfa;

typedef struct dfa {
    state start_state;
    delta* delta; // Transition functions
    int delta_len;
    state* accepting_states;
    int accepting_states_len;
    state error_state;
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

int analyze(int* token_arr_len, char* str, int str_size);
