#include <iostream>
#include <regex>

#define KEYWORD_TOKEN_CLASS_REGEXP '/select/from/where/gi'
#define WHITESPACE_TOKEN_CLASS_REGEXP '/\s/gi'
#define INTEGER_TOKEN_CLASS_REGEXP '/\d+/gi'

using std::cout, std::endl; 

void analyze(char* string, int stringSize)
{
    for(int i=0; i < stringSize; i++)
    {
        std::regex self_regex(KEYWORD_TOKEN_CLASS_REGEXP,
            std::regex_constants::ECMAScript | std::regex_constants::icase);

        if (std::regex_search(s, self_regex)) {
            cout << "Text contains the phrase 'regular expressions'" << endl;
        }

    }
}
