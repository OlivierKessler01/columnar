#pragma once 

#include "generator.h"

struct token {
    string lexeme;
    synthax_cat category;
};

/**
 * RAII'd struct
 */
struct Tokens {
    vector<token> tokens;

    Tokens() 
    {
        tokens = {};
    }
};

/**
 * lexe - Given a request and a list of tokens allocated on the heap
 */
size_t lexe(Tokens &tokens, string str);
