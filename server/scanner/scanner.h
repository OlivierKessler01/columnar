#pragma once 

#include "generator.h"

/**
 * RAII'd struct
 */
struct Tokens {
    token* tokens;
    ssize_t token_len;

    Tokens() 
    {
        tokens = (token*)malloc(0);
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
