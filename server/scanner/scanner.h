#pragma once 

#include <string>
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
ssize_t lexe(Tokens &tokens, std::string str);
