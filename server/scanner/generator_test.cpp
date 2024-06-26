#include <cassert>
#include "../scanner/analyzer.h"
//Include the whole file to be able to test static functions
#include "../scanner/generator.h"
#include <cstdlib>
#include <csignal>

int test_concat_construct()
{
    //A
    state a_accept_state = state{"a_accept_state\n"};
    state a_start_state = state{"a_start_state\n"};
    delta delta_set_a[1];
    delta_set_a[0] = delta{&a_start_state, &a_accept_state};

    nfa a = nfa{};
    a.delta_set_len = 1;
    a.accepting_state = &a_accept_state;
    a.start_state = &a_start_state;
    a.delta_set = delta_set_a;
        
    //B
    state b_accept_state = state{"b_accept_state\n"};
    state b_start_state = state{"b_start_state\n"};
    delta delta_set_b[1];
    delta_set_b[0] = delta{&b_start_state, &b_accept_state};

    nfa b = nfa{};
    b.delta_set_len = 1;
    b.accepting_state = &b_accept_state;
    b.start_state = &b_start_state;
    b.delta_set = delta_set_b;

    nfa* result = (nfa*)malloc(sizeof(nfa));
    concat_construct(&a, &b, result);
    
    //raise(SIGTRAP);
    assert(result->delta_set_len == a.delta_set_len+b.delta_set_len+1);
    assert(result->accepting_state == b.accepting_state);
    assert(result->start_state == a.start_state);
    return EXIT_SUCCESS;
}



int main()
{
    test_concat_construct();
}
