#include "../scanner/scanner.h"
#include "../parser/parser.h"
#include <cstdlib>
#include <stdlib.h>
#include <string>
#include <sys/syslog.h>


/**
 * function run_query - Call the lexer/scanner, then call the parser,
 * then call the query plan builder, then execute the plan.
 *
 * Return the response.
 */
int run_query(string &response, std::string query)
{
    //syslog(LOG_INFO, "in run_query() function");
    Tokens tokens;
    ssize_t len_tokens, result_parser;
    

    //Run the lexer/scanner
    if ((len_tokens = lexe(tokens, query)) == -1) {
        syslog(LOG_INFO, "Wrong request synthax.");
        return -1;
    }
    
    //Run the parser
    if ((result_parser = parse(tokens)) == -1) {
        syslog(LOG_INFO, "Wrong request grammar.");
        return -1;
    }

    //TODO: run the query plan builder
    //TODO: execute the query plan builder
    response = "run_query() response";
    return 1;
}








