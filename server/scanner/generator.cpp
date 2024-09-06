/*
 *  ANSI-SQL scanner generator.
 *  Generates a scanner that can then be compiled and executed to tokenize a string
 *  using ANSI-SQL synthax.
 *
 *	Author: Olivier Kessler <olivier.kessler@protonmail.com>
 */

#include <iostream>
#include <unordered_set>

#define KEYWORD_REGEXP "((select)|(from)|(where))"
#define INTEGER_REGEXP "(0|[1...9][0...9]*)"
#define IDENTIFIER_REGEXP "([a..z]([a..z]|[A...Z]|[0...9])*)"
#define GLOBAL_REGEXP IDENTIFIER_REGEXP "|"  INTEGER_REGEXP "|" KEYWORD_REGEXP 
#include <random>
#include <sstream>
#include <cstring>
#include <memory>
#include <csignal>
#include "generator.h"
#include <stack>

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
    int variant; //0 for literal, 1 for union, 2 for concat, 3 for kleene
    std::shared_ptr<regex_node> left;
    std::shared_ptr<regex_node> right;
    std::string value;

    regex_node(
        int t,
        std::shared_ptr<regex_node> l = nullptr,
        std::shared_ptr<regex_node> r = nullptr,
        std::string v = ""
    ): variant(t), left(l), right(r), value(v) {}
    
    void print() {
        if(variant == 0) {
            print_literal();
        } else if (variant == 1) {
            print_union();
        } else if (variant == 2) {
            print_concat();
        } else if (variant == 3) {
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
 * initialize_nfa - Allocates start and stop state for an nfa.
 */
void initialize_nfa(nfa* nfa)
{
    state start = state{ uuid::generate_uuid_v4() };
    state accept = state{ uuid::generate_uuid_v4()};
    nfa->states[start.name] = start;
    nfa->states[accept.name] = accept;
    nfa->start = start.name;
    nfa->accept = accept.name;
}

/**
 * e_closure - Takes a set of states, returns a set of states reacheable via only
 * epsilon transitions/closures.
 */
void e_closure(
    std::unordered_set<state, state::hash_function>* q,
    std::unordered_set<state, state::hash_function>* result
) {
}

/**
 * delta - Applies the transition function to each element of 
 * q, given a char c.
 */
void delta_func(
    std::unordered_set<state, state::hash_function>* q,
    std::unordered_set<state, state::hash_function>* result,
    char c
) {
}


/**
 * nfa_append - Copies states and transitions from one nfa to another
 */
static void nfa_append(nfa *src, nfa* dest)
{
   for (const auto& [key, value] : src->states) {
        dest->states[key] = value; // Insert or overwrite the value for the key
    }
}

/**
 * add_delta_nfa - Use this function to add a non-epsilon transition to an nfa
 * to maintain a correct sigma set.
 */
static void add_delta_nfa(nfa* nfa, string from_id, string to_id, char character)
{
    nfa->deltas.transitions[from_id][character] = to_id;
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
    
    result->deltas.epsilon_transitions[result->start].push_back(a->start);
    result->deltas.epsilon_transitions[result->start].push_back(b->start);
    result->deltas.epsilon_transitions[a->accept].push_back(result->accept);
    result->deltas.epsilon_transitions[b->accept].push_back(result->accept);
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
    result->deltas.epsilon_transitions[a->accept].push_back(b->start);
}

/**
 * kleene_constuct - Generates an NFA Kleene's closure (a*) construct from an nfa
 *
 * In place algorithm.
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

    state new_start = state{uuid::generate_uuid_v4()};
    state new_accept = state{uuid::generate_uuid_v4()};

    a->start = new_start.name;
    a->accept = new_accept.name;
    a->states[new_start.name] = new_start;
    a->states[new_accept.name] = new_accept;


    a->deltas.epsilon_transitions[new_start.name].push_back(a->accept);
    a->deltas.epsilon_transitions[new_start.name].push_back(old_start);
    a->deltas.epsilon_transitions[old_accept].push_back(old_start);
    a->deltas.epsilon_transitions[old_accept].push_back(a->accept);
}

/**
 * Constructs a non-deterministic automaton from a tree of operations 
 * (kleene, concatenation, union)
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
    if (!node) {
        return EXIT_FAILURE;
    }
    struct nfa nfa_left, nfa_right;
    initialize_nfa(&nfa_left);
    initialize_nfa(&nfa_left);

    if(node->variant == 2) {
        thompson_construction(&nfa_left, node->left);
        thompson_construction(&nfa_right, node->right);
        concat_construct(&nfa_left, &nfa_right, nfa);
    } else if (node->variant == 1) {
        thompson_construction(&nfa_left, node->left);
        thompson_construction(&nfa_right, node->right);
        union_construct(&nfa_left, &nfa_right, nfa);
    } else if (node->variant == 3) {
        kleene_construct(nfa);
    } else if (node->variant == 0) {
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
            nodeStack.push(std::make_shared<regex_node>(3, operand, nullptr, ""));
        } else if (token == "|") {
            auto right = nodeStack.top(); nodeStack.pop();
            auto left = nodeStack.top(); nodeStack.pop();
            nodeStack.push(std::make_shared<regex_node>(1, left, right, ""));
        } else if (token == "·") {
            auto right = nodeStack.top(); nodeStack.pop();
            auto left = nodeStack.top(); nodeStack.pop();
            nodeStack.push(std::make_shared<regex_node>(2, left, right, ""));
        } else {
            // Handle literal or character class
            nodeStack.push(std::make_shared<regex_node>(0, nullptr, nullptr, token)); // Simplified, assumes token is a valid literal
        }
    }

    return nodeStack.top();
}

// Hash set of stated
struct state_set_hash {
    size_t operator()(const std::unordered_set<state> &s) const {
        std::string result;
        for (const auto &state: s){
            result += state.name;
        }
        // Just hash the name field
        return std::hash<string>()(result);
    }
};

// Compare two set of states
struct state_set_pred {
    size_t operator()(const std::unordered_set<state> &s) const {
    }
};

/**
 * Constructs a deterministic finite automaton from a non-deterministic finite
 * automaton.
 */
static void subset_construction(nfa* nfa, dfa* dfa)
{
    std::unordered_set<
        state,
        state::hash_function
    > q0, q, n0_set, t, result;

    std::unordered_set<
        std::unordered_set<state, state::hash_function>,
        state_set_hash,
        state_set_pred
    > worklist,big_q;

    std::unordered_map<
        std::unordered_set<state, state::hash_function>,
        std::unordered_map<char, std::unordered_set<state, state::hash_function>>,
        state_set_hash,
        state_set_pred
    > big_t;

    n0_set.insert(nfa->states[nfa->start]);
    e_closure(&n0_set, &q0);

    big_q.insert(q0);
    worklist.insert(q0);
    
    std::vector<state> current;

    while (!worklist.empty()){
        q.clear();

        // Get an iterator to the first element
        auto it = worklist.begin();
        q = *it;
        // Remove the element from the set
        worklist.erase(q);


        for (auto character: nfa->sigma) {
            result.clear();
            t.clear();
            delta_func(&q, &result, character);
            e_closure(&result, &t); 
             
            big_t[q][character] = t;
            
            if (big_q.count(t) == 0) {
                big_q.insert(t);
                worklist.insert(t);
            }
        }
    }
} 


/**
 * minimize_dfa - Remove duplicates states from the dfa using partitionning/segregation
 */
static void minimize_dfa(dfa* dfa)
{
    //TODO: Minimize the DFA
}

/**
 * generate_scanner_code() - Generate the scanner code as a file. 
 */
static void generate_scanner_code(dfa* dfa)
{
}

/**
 * construct_scanner() - Build the SQL scanner. Output is an executable and dynamically
 * linkeable file.
 * Run this once offline when modifying the language synthax. Then the file
 * will be used to lexe/tokenize at runtime.
 */
int construct_scanner()
{
    nfa nfa;
    initialize_nfa(&nfa);

    dfa * dfa;
    char* code = (char*)malloc(1);
        
    std::cout << "Tree of operations: ";
    auto tokens = re_tokenize(GLOBAL_REGEXP);
    auto postfixTokens = re_to_postfix(tokens);
    std::cout << "Build thompson tree" << endl;
    std::shared_ptr<regex_node> tree = build_thompson_tree(postfixTokens);

    std::cout << "Tree of operations: ";
    tree->print();
    std::cout << std::endl;

    cout << "Converting regexp to nfa" << endl;
    thompson_construction(&nfa, tree);
    cout << "Converting nfa to dfa" << endl;
    //TODO : THIS IF FAILING DUE TO HASHING OF STATES SETS
    subset_construction(&nfa, dfa);
    cout << "Minimizing the dfa" << endl;
    //minimize_dfa(dfa);
    cout << "Generate scanner C++ code as a file." << endl;
    //generate_scanner_code(dfa);

    free(code);
    return 0;
}


#ifdef TEST
#include <cassert>

int test_concat_construct()
{
    nfa a,b, result;
    initialize_nfa(&a);
    initialize_nfa(&b);
    initialize_nfa(&result);

    add_delta_nfa(&a, a.start, a.accept, 'c');
    add_delta_nfa(&b, b.start, b.accept, 'd');

    concat_construct(&a, &b, &result);

    assert(result.accept == b.accept);
    assert(result.start == a.start);
    assert(result.deltas.epsilon_transitions[a.accept].size() == 1);
    
    return EXIT_SUCCESS;
}

int test_union_construct()
{
    nfa a,b, result;
    initialize_nfa(&a);
    initialize_nfa(&b);
    initialize_nfa(&result);

    add_delta_nfa(&a, a.start, a.accept, 'c');
    add_delta_nfa(&b, b.start, b.accept, 'd');

    union_construct(&a, &b, &result);
    
    assert(result.deltas.epsilon_transitions[result.start].size() == 2);
    assert(result.deltas.epsilon_transitions[a.accept].size() == 1);
    assert(result.deltas.epsilon_transitions[b.accept].size() == 1);
    //TODO: Test all deltas
    return EXIT_SUCCESS;
}


int test_kleene_construct()
{
    nfa a;
    initialize_nfa(&a);
    kleene_construct(&a);

    assert(a.deltas.epsilon_transitions[a.start].size() == 2);
    assert(a.deltas.transitions[a.start].size() == 0);
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
