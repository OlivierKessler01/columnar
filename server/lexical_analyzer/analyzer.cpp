#include <iostream>
#include "analyzer.h"

#define KEYWORD_REGEXP "(select)|(from)|(where)"
#define WHITESPACE_REGEXP "\s"
#define INTEGER_REGEXP "0|[1...9][0...9]*"
#define IDENTIFIER_REGEXP "[a..z]([a..z]|[A...Z]|[0...9])*"
#define COMMENT_REGEXP "/\* ([a..z]|[A...Z]|[0...9])*  \*/" 
#define GLOBAL_REGEXP IDENTIFIER_REGEXP "|" WHITESPACE_REGEXP "|" INTEGER_REGEXP "|" KEYWORD_REGEXP "|" COMMENT_REGEXP

using std::cout, std::endl; 



/**
 * Constructs a non-deterministic automaton from a regexp
 */
static nfa* thompson_construction()
{
    cout << "Converting regexp to nfa" << endl;
    nfa* nfa;
    return nfa;
    //TODO: parse the regexp and build
}

/**
 * Constructs a deterministic finite automaton from a non-deterministic finite
 * automaton.
 */
static dfa* subset_construction(nfa* nfa)
{
    cout << "Converting nfa to dfa" << endl;
    dfa* dfa;
    return dfa;
}

token* analyze(int* token_arr_len, char* str, int str_size)
{
    nfa* nfa = thompson_construction();
    dfa * dfa = subset_construction(nfa);
    token* token_arr = recognize(token_arr_len, dfa, str, str_size);
    return token_arr;
}

