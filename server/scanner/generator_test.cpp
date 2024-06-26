#include <cassert>
#include "../scanner/analyzer.h"
//Include the whole file to be able to test static functions
#include "../scanner/generator.h"
#include <cstdlib>

int test_concat_construct()
{
    //A
    state a_accept_state = state{"a_accept_state\n"};
    state a_intermediary_state = state{"a_intermediary_state\n"};
    state a_start_state = state{"a_start_state\n"};
    delta delta_set_a[2];
    delta_set_a[0] = delta{&a_start_state, &a_intermediary_state};
    delta_set_a[1] = delta{&a_intermediary_state, &a_accept_state};

    nfa a = nfa{};
    a.delta_set_len = 2;
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
    
    assert(result->delta_set_len == a.delta_set_len+b.delta_set_len+1);
    assert(result->accepting_state == b.accepting_state);
    assert(result->start_state == a.start_state);
    
    //Check if the epsilon transition is corretly set-up
    bool epsilon_transition = false; 
    delta transition;

    for(int i = 0; i<result->delta_set_len;i++)
    {
        transition = result->delta_set[i];
        if (transition.start_state == a.accepting_state && transition.end_state == b.start_state)
        {
            epsilon_transition = true;
        }
    }
    assert(result->delta_set[0].start_state == a.accepting_state);
    assert(result->delta_set[0].start_state == a.accepting_state);
    assert(epsilon_transition == true);

    free(result);
    return EXIT_SUCCESS;
}

int test_union_construct()
{
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
