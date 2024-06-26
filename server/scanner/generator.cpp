#include <iostream>
#include "../scanner/analyzer.h"

#define KEYWORD_REGEXP "(select)|(from)|(where)"
#define WHITESPACE_REGEXP "\s"
#define INTEGER_REGEXP "0|[1...9][0...9]*"
#define IDENTIFIER_REGEXP "[a..z]([a..z]|[A...Z]|[0...9])*"
#define COMMENT_REGEXP "/\* ([a..z]|[A...Z]|[0...9])*  \*/" 
#define GLOBAL_REGEXP IDENTIFIER_REGEXP "|" WHITESPACE_REGEXP "|" INTEGER_REGEXP "|" KEYWORD_REGEXP "|" COMMENT_REGEXP

using std::cout, std::endl;


/**
 * union_construct - Generates an NFA union construct given two nfas
 */
static void union_construct(nfa* a, nfa* b, nfa* result)
{
}

/**
 * concat_construct - Generates an NFA concatenation construct given nfas
 */
static void concat_construct(nfa* a, nfa* b, nfa* result)
{
    result->start_state = a->start_state;
    result->accepting_state = b->accepting_state;
    
    //A new transition now exists
    result->delta_set_len = a->delta_set_len+b->delta_set_len+1;
    result->delta_set = (delta*)realloc(result, (result->delta_set_len)*sizeof(delta));
    
    //Adding the epsilon transition
    result->delta_set[0] = delta{a->accepting_state, b->start_state };
    
    //Copying states and transitions from a to result
    for(int i=0; i<a->delta_set_len;i++){
        result->delta_set[i] = a->delta_set[i];
    }

    //Copying states and transitions from b to result
    for(int i=0; i<b->delta_set_len;i++){
        result->delta_set[i+a->delta_set_len] = b->delta_set[i];
    }
}

/**
 * kleene_constuct - Generates an NFA Kleene's closure construct given two nfas
 */
static void kleene_construct(nfa* a, nfa* b, nfa* result)
{
}

/**
 * Constructs a non-deterministic automaton from a regexp
 */
static void thompson_construction(nfa* nfa)
{
    cout << "Converting regexp to nfa" << endl;
    //TODO: parse the regexp and build NFA
    
}

/**
 * Constructs a deterministic finite automaton from a non-deterministic finite
 * automaton.
 */
static void subset_construction(nfa* nfa, dfa* dfa)
{
    cout << "Converting nfa to dfa" << endl;
    //TODO: Build DFA from NFA
}

/**
 * minimize_dfa - Remove duplicates states from the dfa using partitionning/segregation
 */
static void minimize_dfa(dfa* dfa)
{
    cout << "Minimizing the dfa" << endl;
    //TODO: Minimize the DFA
}

/**
 * generate_scanner_code - Generate the scanner code as a file. 
 */
static void generate_scanner_code(dfa* dfa)
{
    cout << "Generate scanner C code as a file." << endl;
    //TODO: Create scanner C file from dfa. 
}

/**
 * construct_scanner - Build the SQL scanner. Output is an executable and dynamically
 * linkeable file.
 * Run this once offline when modifying the language synthax. Then the file
 * will be used to lexe/tokenize at runtime.
 */
int construct_scanner()
{
    nfa* nfa;
    dfa * dfa;
    char* code = (char*)malloc(0);
    thompson_construction(nfa);
    subset_construction(nfa, dfa);
    minimize_dfa(dfa);
    generate_scanner_code(dfa);

    free(code);
    free(nfa);
    free(dfa);
    return 0;
}

