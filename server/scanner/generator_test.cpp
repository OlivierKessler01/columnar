#include <cassert>
#include "../scanner/analyzer.h"
//Include the whole file to be able to test static functions
#include "../scanner/generator.cpp"

int test_concat_construct()
{
    nfa a = nfa{};
    nfa b = nfa{};
    nfa result = nfa{};
    concat_construct(&a, &b, &result);

    assert(result.delta_set_len == a.delta_set_len+b.delta_set_len+1);
    return EXIT_SUCCESS;
}



int main()
{
    test_concat_construct();
}
