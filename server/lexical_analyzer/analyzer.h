#pragma once

typedef struct state {
    char name[20];
} state;

typedef struct nfa {
    state start_state;
    state accepting_state;
    state error_state;
} nfa;

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

int analyze(token* token_arr, char* str, int str_size);
