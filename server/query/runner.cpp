#include "../lexical_analyzer/analyzer.h"
#include "../parser/parser.h"
#include <cstddef>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using std::cout, std::endl; 

/**
 * function run_query - Call the lexer/scanner, then call the parser,
 * then call the query plan builder, then execute the plan.
 *
 * Return the response.
 */
char* run_query(int *resp_size, char* query, ssize_t query_len)
{
    cout << "in run_query() function" << endl;
    token* tokens = NULL;
    size_t result;

    //Run the lexer/scanner
    if ((result_lexer = lexe(&tokens, query, query_len)) == -1) {
        cout << "Wrong request synthax" << endl;
    }
    
    //Run the parser
    if ((result_parser = parse(&tokens, result_lexer)) == -1) {
        cout << "Wrong request synthax" << endl;
    }

    //TODO: run the query plan builder
    //TODO: execute the query plan builder

    char* response = (char*)malloc(21);
    const char* response_s = "run_query() response";
    strcpy(response, response_s);
    *resp_size = 21;
    return response;
}








