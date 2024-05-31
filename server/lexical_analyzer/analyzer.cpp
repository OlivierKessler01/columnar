#include <iostream>
#include "analyzer.h"

#define KEYWORD_TOKEN_CLASS_REGEXP "(select)|(from)|(where)"
#define WHITESPACE_TOKEN_CLASS_REGEXP "\s"
#define INTEGER_TOKEN_CLASS_REGEXP "0|[1...9][0...9]*"
#define IDENTIFIER_REGEXP "[a..z]([a..z]|[A...Z]|[0...9])*"
#define COMMENT_REGEXP "/\* ([a..z]|[A...Z]|[0...9])*  \*/" 

using std::cout, std::endl; 


/**
 * Constructs a non-deterministic automaton from a regexp
 */
static void thompson_construction(nfa* nfa)
{
    cout << "Converting regexp to nfa" << endl;
    //TODO: parse the regexp and build
}

int analyze(token* token_arr, char* str, int str_size)
{
    nfa* nfa;
    thompson_construction(nfa);
    //convert nfa to dfa 
    return 1;
}

