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
#include <random>
#include <sstream>

using std::cout, std::endl;

namespace uuid {
    static std::random_device              rd;
    static std::mt19937                    gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);
    
    /**
     * Generates UUIDs with 32 bits of randomness
     * Number of possible combinations : approx 4E9
     * Should be enough for the number of states we use
     */
    std::string generate_uuid_v4() {
        std::stringstream ss;
        int i;
        ss << std::hex;
        for (i = 0; i < 8; i++) {
            ss << dis(gen);
        }
        ss << "-";
        for (i = 0; i < 4; i++) {
            ss << dis(gen);
        }
        ss << "-4";
        for (i = 0; i < 3; i++) {
            ss << dis(gen);
        }
        ss << "-";
        ss << dis2(gen);
        for (i = 0; i < 3; i++) {
            ss << dis(gen);
        }
        ss << "-";
        for (i = 0; i < 12; i++) {
            ss << dis(gen);
        };
        return ss.str();
    }
}

/**
 * Copies states and transitions from one nfa to another
 */
static void nfa_append(nfa *src, nfa* dest)
{
    for (const auto& [key, value] : src->deltas){
        dest->deltas[key].insert(
            dest->deltas[key].end(),
            src->deltas[key].begin(),
            src->deltas[key].end()
        );
    }
}

/**
 * union_construct - Generates an NFA union construct (a|b) given two nfas
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
    first.from = result->start;
    first.to = a->start;
    first.epsilon = true;
    result->deltas[result->start].push_back(first);

    delta second = delta{};
    second.from = result->start;
    second.to = b->start;
    second.epsilon = true;
    result->deltas[result->start].push_back(second);

    delta third = delta{};
    third.from = a->accept;
    third.to = result->accept;
    third.epsilon = true;
    result->deltas[a->accept].push_back(third);

    delta fourth = delta{};
    fourth.from = b->accept;
    fourth.to = result->accept;
    third.epsilon = true;
    result->deltas[b->accept].push_back(fourth);
}


static void allocate_nfa(nfa* nfa)
{
    nfa->start = uuid::generate_uuid_v4();
    nfa->accept = uuid::generate_uuid_v4();
}


/**
 * concat_construct - Generates an NFA concatenation construct (ab) given two nfas
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
    first.from = a->accept;
    first.to = b->start;
    first.epsilon = true;
    result->deltas[a->accept].push_back(first);
}

/**
 * kleene_constuct - Generates an NFA Kleene's closure (a*) construct from an nfa
 *    
 *
 *        (New Start State)
 *               |
 *              ε|ε
 *               |
 *         +-----+----------+
 *         |                |
 *         v                | 
 *  (Start State of A)      | 
 *         |         ^      |
 *        ...        |      | 
 *         |         |ε     |
 *         v         |      | 
 * (Accepting State of A)   | 
 *         |                |
 *          \              /
 *          ε\            /
 *            v          v
 *        (New Accepting State)
 */
static void kleene_construct(nfa* a, nfa* result)
{
    //Copy state and transitions from a and b to result
    nfa_append(a,result);

    delta empty = delta{};
    empty.from = result->start;
    empty.to = result->accept;
    empty.epsilon = true;


    delta to_a = delta{};
    to_a.from = result->start;
    to_a.to = a->start;
    to_a.epsilon = true;

    delta feedback = delta{};
    feedback.from = a->accept;
    feedback.to = a->start;
    empty.epsilon = true;

    delta stop = delta{};
    stop.from = a->accept;
    stop.to = result->accept;
    stop.epsilon = true;

    result->deltas[result->start].push_back(empty);
    result->deltas[result->start].push_back(to_a);
    result->deltas[a->accept].push_back(feedback);
    result->deltas[a->accept].push_back(stop);
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
    first.from = "1";
    first.to = "2";
    first.input = 'c';

    a.deltas[first.from].push_back(first);

    //B
    delta second;
    second.from = "3";
    second.to = "4";
    second.input = 'd';

    b.deltas[second.from].push_back(second);

    concat_construct(&a, &b, &result);

    assert(result.accept == b.accept);
    assert(result.start == a.start);
    assert(result.deltas.at(a.accept).size() == 1 );
    
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
    first.from = "1";
    first.to = "2";
    first.input = 'c';

    a.deltas[first.from].push_back(first);

    //B
    delta second;
    second.from = "3";
    second.to = "4";
    second.input = 'd';

    b.deltas[second.from].push_back(second);

    union_construct(&a, &b, &result);

    assert(result.deltas.at(result.start).size() == 2);
    assert(result.deltas.at(b.accept).size() == 1);
    assert(result.deltas.at(a.accept).size()== 1);
    //TODO: Test all deltas
    //
    return EXIT_SUCCESS;
}

int test_kleene_construct()
{
    nfa a,result;
    allocate_nfa(&a);
    allocate_nfa(&result);

    kleene_construct(&a, &result);

    assert(result.deltas.at(result.start).size() == 2);
    assert(result.deltas.at(a.accept).size() == 2);
    return EXIT_SUCCESS;
}

int main()
{
    test_concat_construct();
    test_union_construct();
    test_kleene_construct();
}
#endif
