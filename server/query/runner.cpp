#include "../lexical_analyzer/analyzer.h"
#include "../parser/parser.h"
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
char* run_query(int *resp_size, char* query, int query_len)
{
    cout << "in run_query() function" << endl;
    token* token_arr = NULL;
    int token_arr_len = 0;
    //Run the lexer/scanner
    token_arr_len = analyze(token_arr, query, query_len);
    //Run the parser
    parse(token_arr, token_arr_len);

    //TODO: run the query plan builder
    //TODO: execute the query plan builder

    char* response = (char*)malloc(21);
    const char* response_s = "run_query() response";
    strcpy(response, response_s);
    *resp_size = 21;
    return response;
}








