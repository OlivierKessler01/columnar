/*
 *  ANSI-SQL scanner generator.
 *  Generates a scanner that can then be compiled and executed to tokenize a string
 *  using ANSI-SQL synthax.
 *
 *	Author: Olivier Kessler <olivier.kessler@protonmail.com>
 */

#include <iostream>
#include "analyzer.h"

#define KEYWORD_REGEXP "((select)|(from)|(where))"
#define INTEGER_REGEXP "(0|[1...9][0...9]*)"
#define IDENTIFIER_REGEXP "([a..z]([a..z]|[A...Z]|[0...9])*)"
#define GLOBAL_REGEXP IDENTIFIER_REGEXP "|"  INTEGER_REGEXP "|" KEYWORD_REGEXP 
#include <random>
#include <sstream>
#include <cstring>
#include <stack>
#include <memory>

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

// Base struct for a regex node
struct regex_node {
    std::shared_ptr<regex_node> left;
    std::shared_ptr<regex_node> right;
    std::string value;
    int type; //0 for literal, 1 for union, 2 for concat, 3 for kleene

    regex_node(
        int t,
        std::shared_ptr<regex_node> l,
        std::shared_ptr<regex_node> r,
        std::string v
    ): type(t), left(l), right(r), value(v) {}
    
    void print() {
        if(type == 0) {
            print_literal();
        } else if (type == 1) {
            print_union();
        } else if (type == 2) {
            print_concat();
        } else if (type == 3) {
            print_kleene();
        } else {
            std::cout << "Wrong Regex node type" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    private:
        void print_literal() {
            std::cout << "Literal(" << value << ")";
        }

        void print_union() {
            std::cout << "Union(";
            left->print();
            std::cout << ", ";
            right->print();
            std::cout << ")";
        }

        void print_concat() {
            std::cout << "Concat(";
            left->print();
            std::cout << ", ";
            right->print();
            std::cout << ")";
        }
        
        //left will be used to store the only operand for a kleene's closure
        void print_kleene() {
            std::cout << "KleeneStar(";
            left->print();
            std::cout << ")";
        }
};


/**
 * nfa_append - Copies states and transitions from one nfa to another
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
static void kleene_construct(nfa* a)
{
    std::string old_start, old_accept;
    old_start = a->start;
    old_accept = a->accept;

    delta empty = delta{};
    empty.from = a->start;
    empty.to = a->accept;
    empty.epsilon = true;

    delta to_a = delta{};
    to_a.from = a->start;
    to_a.to = old_start;
    to_a.epsilon = true;

    delta feedback = delta{};
    feedback.from = old_accept;
    feedback.to = old_start;
    empty.epsilon = true;

    delta stop = delta{};
    stop.from = old_accept;
    stop.to = a->accept;
    stop.epsilon = true;

    a->deltas[a->start].push_back(empty);
    a->deltas[a->start].push_back(to_a);
    a->deltas[old_accept].push_back(feedback);
    a->deltas[old_accept].push_back(stop);
}

/**
 * Constructs a non-deterministic automaton from a tree of operations 
 * (kleene, concatenation, union(
 *
 * Args:
 *      nfa : An empty but initialized nfa object
 *      node: The root when first callind
 *
 * Returns:
 *      -1 if failure
 */
static int thompson_construction(nfa* nfa, std::shared_ptr<regex_node> node)
{
    struct nfa nfa_left, nfa_right;
    
    if(node->type == 2) {
        thompson_construction(&nfa_left, node->left);
        thompson_construction(&nfa_right, node->right);
        concat_construct(&nfa_left, &nfa_right, nfa);
    } else if (node->type == 1) {
        thompson_construction(&nfa_left, node->left);
        thompson_construction(&nfa_right, node->right);
        union_construct(&nfa_left, &nfa_right, nfa);
    } else if (node->type == 3) {
        kleene_construct(nfa);
    } else if (node->type == 0) {
    } else {
        cout << "Wrong regex node type" << endl;
        exit(EXIT_FAILURE);
    }
    
    return EXIT_SUCCESS;
}


/**
 * re_tokenize - Given a regexp, returns a stream of tokens representing
 * all the elements of the regexp.
 */
static std::vector<std::string> re_tokenize(const std::string &regex) {
    std::vector<std::string> tokens;
    std::string token;
    bool inClass = false;

    for (size_t i = 0; i < regex.size(); ++i) {
        char c = regex[i];

        if (c == '[') {
            inClass = true;
            token += c;
        } else if (c == ']') {
            inClass = false;
            token += c;
            tokens.push_back(token);
            token.clear();
        } else if (inClass || (isalnum(c) && !token.empty() && isalnum(token.back()))) {
            token += c;
        } else {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            if (c == '(' || c == ')' || c == '|' || c == '*' || c == '\xB7') {
                tokens.push_back(std::string(1, c));
            } else if (isalnum(c)) {
                token += c;
            }
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}

/**
 * re_to_postfix - Given a stream of tokens reprensenting a regexp in the infix
 * format, convert it to postfix using the shunting yard algorithm.
 */
static std::vector<std::string> re_to_postfix(const std::vector<std::string> &tokens) {
    std::vector<std::string> output;
    std::stack<std::string> operators;
    std::unordered_map<std::string, int> precedence = {{"*", 3}, {"·", 2}, {"|", 1}};
    std::unordered_map<std::string, bool> rightAssociative = {{"*", true}, {"·", false}, {"|", false}};

    auto isOperator = [&](const std::string &token) {
        return precedence.find(token) != precedence.end();
    };

    for (const auto &token : tokens) {
        if (isalnum(token[0]) || token == " " || token[0] == '[') {
            output.push_back(token);
        } else if (token == "(") {
            operators.push(token);
        } else if (token == ")") {
            while (!operators.empty() && operators.top() != "(") {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.pop(); // Pop the '('
        } else if (isOperator(token)) {
            while (!operators.empty() && operators.top() != "(" &&
                   (precedence[operators.top()] > precedence[token] ||
                    (precedence[operators.top()] == precedence[token] && !rightAssociative[token]))) {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.push(token);
        }
    }

    while (!operators.empty()) {
        output.push_back(operators.top());
        operators.pop();
    }

    return output;
}

/**
 * build_thompson_tree - Build a tree from a stream of regexp tokens in the 
 * postfix format.
 */
static std::shared_ptr<regex_node> build_thompson_tree(
    const std::vector<std::string> &postfixTokens
) {
    std::stack<std::shared_ptr<regex_node>> nodeStack;

    for (const auto &token : postfixTokens) {
        if (token == "*") {
            auto operand = nodeStack.top(); nodeStack.pop();
            nodeStack.push(std::make_shared<regex_node>(3, operand, NULL, NULL));
        } else if (token == "|") {
            auto right = nodeStack.top(); nodeStack.pop();
            auto left = nodeStack.top(); nodeStack.pop();
            nodeStack.push(std::make_shared<regex_node>(1, left, right, NULL));
        } else if (token == "·") {
            auto right = nodeStack.top(); nodeStack.pop();
            auto left = nodeStack.top(); nodeStack.pop();
            nodeStack.push(std::make_shared<regex_node>(2, left, right, NULL));
        } else {
            // Handle literal or character class
            nodeStack.push(std::make_shared<regex_node>(0, NULL, NULL, token)); // Simplified, assumes token is a valid literal
        }
    }

    return nodeStack.top();
}

/**
 * Constructs a deterministic finite automaton from a non-deterministic finite
 * automaton.
 */
static void subset_construction(nfa* nfa, dfa* dfa)
{
    //TODO: Build DFA from NFA
}

/**
 * minimize_dfa - Remove duplicates states from the dfa using partitionning/segregation
 */
static void minimize_dfa(dfa* dfa)
{
    //TODO: Minimize the DFA
}

/**
 * generate_scanner_code - Generate the scanner code as a file. 
 */
static void generate_scanner_code(dfa* dfa)
{
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

    auto tokens = re_tokenize(GLOBAL_REGEXP);
    auto postfixTokens = re_to_postfix(tokens);
    std::shared_ptr<regex_node> tree = build_thompson_tree(postfixTokens);

    std::cout << "Tree of operations: ";
    tree->print();
    std::cout << std::endl;

    cout << "Converting regexp to nfa" << endl;
    thompson_construction(nfa, tree);
    cout << "Converting nfa to dfa" << endl;
    subset_construction(nfa, dfa);
    cout << "Minimizing the dfa" << endl;
    minimize_dfa(dfa);
    cout << "Generate scanner C++ code as a file." << endl;
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

    kleene_construct(&a);

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
#else

int main()
{
    construct_scanner();
}

#endif
