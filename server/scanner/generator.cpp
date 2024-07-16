/*
 *  ANSI-SQL scanner generator.
 *  Generates a scanner that can then be compiled and executed to tokenize a string
 *  using ANSI-SQL synthax.
 *
 *	Author: Olivier Kessler <olivier.kessler@protonmail.com>
 */

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
 * Copies states and transitions from one nfa to another
 */
static void nfa_append(nfa *src, nfa* dest)
{
    for (const auto& [key, value] : src->delta_inorder){
         dest->delta_inorder[key].insert(
            dest->delta_inorder[key].end(),
            src->delta_inorder[key].begin(),
            src->delta_inorder[key].end()
        );
    }

    for (const auto& [key, value] : src->delta_inverse){
         dest->delta_inverse[key].insert(
            dest->delta_inverse[key].end(),
            src->delta_inverse[key].begin(),
            src->delta_inverse[key].end()
        );
    }
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
    nfa_append(a,result);
    nfa_append(b,result);
    
    delta first = delta{};
    first.start_state = result->start;
    first.end_state = a->start;
    first.epsilon = true;
    result->delta_inorder[result->start].push_back(first);
    first.start_state = a->start;
    first.end_state = result->start;
    result->delta_inverse[a->start].push_back(first);

    delta second = delta{};
    second.start_state = result->start;
    second.end_state = b->start;
    second.epsilon = true;
    result->delta_inorder[result->start].push_back(second);
    second.start_state = b->start;
    second.end_state = result->start;
    result->delta_inverse[b->start].push_back(second);

    delta third = delta{};
    third.start_state = a->accept;
    third.end_state = result->accept;
    third.epsilon = true;
    result->delta_inorder[a->accept].push_back(third);
    third.start_state = result->accept;
    third.end_state = a->accept;
    result->delta_inverse[result->accept].push_back(third);

    delta fourth = delta{};
    fourth.start_state = b->accept;
    fourth.end_state = result->accept;
    third.epsilon = true;
    result->delta_inorder[b->accept].push_back(fourth);
    fourth.start_state = result->accept;
    fourth.end_state = b->accept;
    result->delta_inverse[result->accept].push_back(fourth);
}


static void allocate_nfa(nfa* nfa)
{
    //TODO generate random UUIDs
    nfa->start = "start";
    nfa->accept = "accept";
}


/**
 * concat_construct - Generates an NFA concatenation construct given two nfas
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
    //Copy state and transitions from a and b to result
    nfa_append(a,result);
    nfa_append(b,result);
    result->start = a->start;
    result->accept = b->accept;

    //Add the epsilon transitions
    delta first = delta{};
    first.start_state = a->accept;
    first.end_state = b->start;
    first.epsilon = true;
    result->delta_inorder[a->accept].push_back(first);
    first.start_state = b->start;
    first.end_state = a->accept;
    result->delta_inverse[b->start].push_back(first);
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
    return 0;
}


#ifdef TEST
#include <cassert>

int test_concat_construct()
{
    nfa a,b,result;
    allocate_nfa(&a);
    allocate_nfa(&b);
    allocate_nfa(&result);

    //A
    delta first;
    first.start_state = "1";
    first.end_state = "2";
    first.input = 'c';

    a.delta_inorder[first.start_state].push_back(first);
    a.delta_inverse[first.end_state].push_back(first);

    //B
    delta second;
    second.start_state = "3";
    second.end_state = "4";
    second.input = 'd';

    b.delta_inorder[second.start_state].push_back(second);
    b.delta_inverse[second.end_state].push_back(second);

    concat_construct(&a, &b, &result);

    assert(result.accept == b.accept);
    assert(result.start == a.start);
    

    return EXIT_SUCCESS;
}

int test_union_construct()
{
    nfa a,b,result;
    allocate_nfa(&a);
    allocate_nfa(&b);
    allocate_nfa(&result);

    //A
    delta first;
    first.start_state = "1";
    first.end_state = "2";
    first.input = 'c';

    a.delta_inorder[first.start_state].push_back(first);
    a.delta_inverse[first.end_state].push_back(first);

    //B
    delta second;
    second.start_state = "3";
    second.end_state = "4";
    second.input = 'd';

    b.delta_inorder[second.start_state].push_back(second);
    b.delta_inverse[second.end_state].push_back(second);

    union_construct(&a, &b, &result);


    //TODO: Test all deltas
    //
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
