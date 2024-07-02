/*
 *  ANSI-SQL scanner generator.
 *  Generates a scanner that can then be compiled and executed to tokenize a string
 *  using ANSI-SQL synthax.
 *
 *	Author: Olivier Kessler <olivier.kessler@protonmail.com>
 */



#include <cstring>
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
 *
 *        (New Start State)
 *               |
 *              ε|ε
 *               |
 *         +-----+-----+
 *         |           |
 *         v           v
 * (Start State of A)  (Start State of B)
 *         |           |
 *        ...         ... : those are inside layers of a and b, could be a complex nfas
 *         |           |
 *         v           v
 *(Accepting State of A) (Accepting State of B)
 *         |           |
 *          \         /
 *           ε\     /ε
 *             v   v
 *      (New Accepting State)
 */
static void union_construct(nfa* a, nfa* b, nfa* result)
{
    strcpy(result->start_state->name, "start union state\n");
    strcpy(result->accepting_state->name, "accepting union state\n");

    result->delta_set_len = a->delta_set_len+b->delta_set_len+4;
    result->delta_set = (delta*)malloc(result->delta_set_len*sizeof(delta));
}

/**
 * concat_construct - Generates an NFA concatenation construct given two nfas
 *
 *
 *   (Start State of A)
 *         |
 *        ...  
 *         |
 *   (Accepting State of A)
 *         |
 *        ε|
 *         |
 *   (Start State of B)
 *         |
 *        ... 
 *         |
 *   (Accepting State of B)
 */
static void concat_construct(nfa* a, nfa* b, nfa* result)
{
    result->start_state = a->start_state;
    result->accepting_state = b->accepting_state;
    
    //A new transition now exists
    result->delta_set_len = a->delta_set_len+b->delta_set_len+1;
    
    //Adding the epsilon transition
    result->delta_set = (delta*)malloc(result->delta_set_len*sizeof(delta));
    result->delta_set[0] = delta{a->accepting_state, true, b->start_state };
    
    //Copying states and transitions from a to result
    for(int i=0; i<a->delta_set_len;i++){
        result->delta_set[i+1] = a->delta_set[i];
    }

    //Copying states and transitions from b to result
    for(int i=0; i<b->delta_set_len;i++){
        result->delta_set[i+a->delta_set_len+1] = b->delta_set[i];
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
    free(nfa->delta_set);
    free(dfa->delta_set);
    free(dfa->accepting_states);
    return 0;
}


#ifdef TEST
#include <cassert>

int test_concat_construct()
{
    nfa a,b,result;

    //A
    state a_accept_state = state{"a_accept_state\n"};
    state a_intermediary_state = state{"a_interm_state\n"};
    state a_start_state = state{"a_start_state\n"};
    delta delta_set_a[2];

    a.delta_set_len = 2;
    a.accepting_state = &a_accept_state;
    a.start_state = &a_start_state;
    a.delta_set = delta_set_a;
    a.delta_set[0] = delta{&a_start_state, 'z', &a_intermediary_state};
    a.delta_set[1] = delta{&a_intermediary_state, 'x',  &a_accept_state};
    
    //B
    state b_accept_state = state{"b_accept_state\n"};
    state b_start_state = state{"b_start_state\n"};
    delta delta_set_b[1];

    b.delta_set_len = 1;
    b.accepting_state = &b_accept_state;
    b.start_state = &b_start_state;
    b.delta_set = delta_set_b;
    b.delta_set[0] = delta{&b_start_state, 'w', &b_accept_state};

    concat_construct(&a, &b, &result);
    
    assert(result.delta_set_len == a.delta_set_len+b.delta_set_len+1);
    assert(result.accepting_state == b.accepting_state);
    assert(result.start_state == a.start_state);
    
    //Check if the epsilon transition is corretly set-up
    bool epsilon_transition = false; 
    delta transition;

    for(int i = 0; i<result.delta_set_len;i++)
    {
        transition = result.delta_set[i];
        if (transition.start_state == a.accepting_state && transition.end_state == b.start_state)
        {
            epsilon_transition = true;
        }
    }
    assert(result.delta_set[0].start_state == a.accepting_state);
    assert(result.delta_set[0].start_state == a.accepting_state);
    assert(epsilon_transition == true);

    free(result.delta_set);

    return EXIT_SUCCESS;
}

int test_union_construct()
{
    nfa a,b,result;

    //A
    state a_accept_state = state{"a_accept_state\n"};
    state a_intermediary_state = state{"a_interm_state\n"};
    state a_start_state = state{"a_start_state\n"};
    delta delta_set_a[2];

    a.delta_set_len = 2;
    a.accepting_state = &a_accept_state;
    a.start_state = &a_start_state;
    a.delta_set = delta_set_a;
    a.delta_set[0] = delta{&a_start_state, 'z', &a_intermediary_state};
    a.delta_set[1] = delta{&a_intermediary_state, 'x',  &a_accept_state};
    
    //B
    state b_accept_state = state{"b_accept_state\n"};
    state b_start_state = state{"b_start_state\n"};
    delta delta_set_b[1];

    b.delta_set_len = 1;
    b.accepting_state = &b_accept_state;
    b.start_state = &b_start_state;
    b.delta_set = delta_set_b;
    b.delta_set[0] = delta{&b_start_state, 'w', &b_accept_state};

    union_construct(&a, &b, &result);
    assert(result.delta_set_len == a.delta_set_len+b.delta_set_len+4);
    free(result.delta_set);

    //TODO: Test all deltas
    return EXIT_SUCCESS;
}

int test_kleene_construct()
{
    return EXIT_SUCCESS;
}

int main()
{
    test_concat_construct();
    test_union_construct();
    test_kleene_construct();
}
#endif
