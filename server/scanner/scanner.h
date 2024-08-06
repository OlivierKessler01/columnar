#pragma once 

#include "generator.h"

struct token {
    char* lexeme;
    synthax_cat category;
};

/**
 * RAII'd struct
 */
struct Tokens {
    token* tokens;
    ssize_t token_len;

    Tokens() 
    {
        tokens = (token*)malloc(sizeof(token)*1);
        token_len = 0;
    }

    ~Tokens() 
    {
        free(tokens);
    }
};

/**
 * lexe - Given a request and a list of tokens allocated on the heap
 *
 */
size_t lexe(Tokens* tokens, char* str, ssize_t str_size);
