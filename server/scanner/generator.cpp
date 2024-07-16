/*
 *  ANSI-SQL scanner generator.
 *  Generates a scanner that can then be compiled and executed to tokenize a string
 *  using ANSI-SQL synthax.
 *
 *	Author: Olivier Kessler <olivier.kessler@protonmail.com>
 */

#include <cstring>
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
 * Deep copies states and transitions from an nfa to another
 *
 * Returns the index at which the added states start in the state array
 */
static int nfa_append(nfa *src, nfa* dest)
{
    int initial_state_set_len = dest->state_set_len;
    int initial_delta_set_len = dest->delta_set_len;
    int new_state_set_len = dest->state_set_len+src->state_set_len;
    int new_delta_set_len = dest->delta_set_len+src->delta_set_len;

    dest->state_set = (state*)realloc(dest->state_set, new_state_set_len*sizeof(state));
    dest->delta_set = (delta*)realloc(dest->delta_set, new_delta_set_len*sizeof(delta));
    
    //Copying states
    for(int i=0; i<src->state_set_len;i++){
        strcpy(src->state_set[i+initial_state_set_len].name, src->state_set[i].name);
    }

    //Copying transitions
    for(int i=0; i<src->delta_set_len;i++){
        dest->delta_set[i+initial_delta_set_len] = src->delta_set[i];
    }

    return initial_state_set_len;
}

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
    //Copy state and transitions from a and b to result
    int offset_a = nfa_append(a,result);
    int offset_b = nfa_append(b,result);
    
    //Adding 4 new epsilons transitions
    result->delta_set_len = a->delta_set_len+b->delta_set_len+4;
    result->delta_set = (delta*)realloc(result->delta_set, result->delta_set_len*sizeof(delta));

    result->delta_set[result->delta_set_len-4].start_state = &(result->state_set[0]);
    result->delta_set[result->delta_set_len-4].end_state = &(result->state_set[offset_a]);

    result->delta_set[result->delta_set_len-4].start_state = &(result->state_set[0]);
    result->delta_set[result->delta_set_len-4].end_state = &(result->state_set[offset_b]);


    result->delta_set[result->delta_set_len-4].start_state = &(result->state_set[offset_b+1]);
    result->delta_set[result->delta_set_len-4].end_state = &(result->state_set[1]);

    result->delta_set[result->delta_set_len-4].start_state = &(result->state_set[offset_a+1]);
    result->delta_set[result->delta_set_len-4].end_state = &(result->state_set[1]);
}


static void allocate_nfa(nfa* nfa)
{
    nfa->delta_set = (delta*)malloc(0);
    nfa->delta_set_len = 0;
    nfa->state_set = (state*)malloc(2*sizeof(state));
    nfa->state_set_len = 2;
    nfa->state_set[0] = state{"start"};
    nfa->state_set[1] = state{"accept"};
}

static void deallocate_nfa(nfa* nfa)
{
    free(nfa->delta_set);
    free(nfa->state_set);
}

static void allocate_dfa(dfa* dfa)
{
}

static void deallocate_dfa(dfa* dfa)
{
}

/**
 * concat_construct - Generates an NFA concatenation construct given two nfas
 *
 *   (New start state)
 *         |
 *        ε|
 *         |
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
 *         |
 *        ε|
 *         |
 *   (New accepting state)
 */
static void concat_construct(nfa* a, nfa* b, nfa* result)
{
    //Copy state and transitions from a and b to result
    int offset_a = nfa_append(a,result);
    int offset_b = nfa_append(b,result);

    //Add the 3 new epsilon transitions
    result->delta_set_len +=3;
    result->delta_set = (delta*)realloc(result->delta_set, result->delta_set_len);

    result->delta_set[result->delta_set_len -1].start_state = &(result->state_set[offset_a+1]);
    result->delta_set[result->delta_set_len -1].end_state = &(result->state_set[offset_b]); 
    result->delta_set[result->delta_set_len -1].epsilon = true;

    result->delta_set[result->delta_set_len -2].start_state = &(result->state_set[0]);
    result->delta_set[result->delta_set_len -2].end_state = &(result->state_set[offset_a]); 
    result->delta_set[result->delta_set_len -2].epsilon = true;

    result->delta_set[result->delta_set_len -3].start_state = &(result->state_set[1]);
    result->delta_set[result->delta_set_len -3].end_state = &(result->state_set[offset_b+1]); 
    result->delta_set[result->delta_set_len -3].epsilon = true;
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
    deallocate_nfa(nfa);
    deallocate_dfa(dfa);
    return 0;
}


#ifdef TEST
#include <cassert>

int test_concat_construct()
{
    nfa a,b,result;
    allocate_nfa(a);
    allocate_nfa(b);
    allocate_nfa(result);

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

    deallocate_nfa(result);
    deallocate_nfa(a);
    deallocate_nfa(b);

    return EXIT_SUCCESS;
}

int test_union_construct()
{
    nfa a,b,result;
    allocate_nfa(&a);
    allocate_nfa(&b);
    allocate_nfa(&result);

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
    a.state_set_len = 1;
    a.state_set = (state*)realloc(sizeof(state);
    a.state_set[0] = a_intermediary_state;
    
    //B
    state b_accept_state = state{"b_accept_state\n"};
    state b_intermediary_state = state{"b_interm_state\n")
    state b_start_state = state{"b_start_state\n"};
    delta delta_set_b[2];

    b.delta_set_len = 2;
    b.accepting_state = &b_accept_state;
    b.start_state = &b_start_state;
    b.delta_set = delta_set_b;
    b.delta_set[0] = delta{&b_start_state, 'w', &b_intermediary_state};
    a.delta_set[1] = delta{&b_intermediary_state, 'x',  &b_accept_state};
    b.state_set_len = 1;
    b.state_set = (state*)realloc(sizeof(state));
    b.state_set[0] = b_intermediary_state;

    union_construct(&a, &b, &result);
    assert(result.delta_set_len == a.delta_set_len+b.delta_set_len+4);
    
    
    bool epsilon_to_start_of_b, epsilon_to_start_of_a = false;
    bool epsilon_from_end_of_b, epsilon_from_end_of_a = false;
    delta delt;

    for(int i=0;i<result.delta_set_len;i++)
    {
        delt = result.delta_set[i];
        
        if (strcmp(delt.start_state->name, result.start_state->name) == 0){
            if(strcmp(delt.end_state->name,a.start_state->name) == 0){
                epsilon_to_start_of_a = true;
            }
            if(strcmp(delt.end_state->name,b.start_state->name) == 0){
                epsilon_to_start_of_b = true;
            }
        }
        
        
        if (strcmp(delt.end_state->name, result.accepting_state->name) == 0){
            if(strcmp(delt.start_state->name,a.accepting_state->name) == 0){
                epsilon_from_end_of_a = true;
            }
            if(strcmp(delt.start_state->name,b.accepting_state->name) == 0){
                epsilon_from_end_of_b = true;
            }
        }
    }
    
    assert(epsilon_to_start_of_b == true);
    assert(epsilon_to_start_of_a == true);
    assert(epsilon_from_end_of_b = true);
    assert(epsilon_from_end_of_a = true);
    
    deallocate_nfa(&a);
    deallocate_nfa(&b);
    deallocate_nfa(&result);

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
