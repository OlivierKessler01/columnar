#include <cassert>

int test_concat_construct()
{
    nfa a = nfa{};
    nfa b = nfa{};
    nfa result = nfa{};
    test_concat_construct(&a, &b, &result);

    assert(result.delta_set_len == a.delta_set_len+b.delta_set_len+1);
}





int main()
{
    assert(test_concat_construct() == true);
}
