/*
 *  ANSI-SQL scanner generator.
 *  Generates a scanner that can then be compiled and executed to tokenize a
 *string using ANSI-SQL synthax.
 *
 *	Author: Olivier Kessler <olivier.kessler@protonmail.com>
 */

#include <ios>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

#define KEYWORD_REGEXP "((select)|(from)|(where))"
#define INTEGER_REGEXP "((0)|([1-9]([0-9])*))"
#define IDENTIFIER_REGEXP "([a-Z]([a-Z]|[0-9])*)"
#define OPERATOR_REGEXP "(\\*|\\+|\\-)"
#define END_LINE_REGEXP "(;)"
#include "generator.h"
#include <csignal>
#include <cstring>
#include <ctype.h>
#include <memory>
#include <random>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using std::cout, std::endl, std::vector, std::unordered_map, std::unordered_set;

namespace uuid {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);

    /**
     * Generates UUIDs with 32 bits of randomness
     * Number of possible combinations : approx 4E9
     * Should be enough for the number of states we use
     */
    string generate_uuid_v4() {
        stringstream ss;
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

struct regex_node {
    int variant; // 0 for literal, 1 for union, 2 for concat, 3 for kleene
    std::shared_ptr<regex_node> left;
    std::shared_ptr<regex_node> right;
    string value;

    regex_node(int t, std::shared_ptr<regex_node> l = nullptr,
               std::shared_ptr<regex_node> r = nullptr, string v = "")
        : variant(t), left(l), right(r), value(v) {}

    void print(int indent = 0) {
        string padding(indent, ' '); // Indentation for tree structure
        if (variant == 0) {
            std::cout << padding << "📄 Literal: " << value << "\n";
        } else if (variant == 1) {
            std::cout << padding << "🔀 Union\n";
            left->print(indent + 4);
            right->print(indent + 4);
        } else if (variant == 2) {
            std::cout << padding << "🔗 Concat\n";
            left->print(indent + 4);
            right->print(indent + 4);
        } else if (variant == 3) {
            std::cout << padding << "⭐ Kleene Star\n";
            left->print(indent + 4);
        } else {
            std::cout << padding << "⚠️ Wrong Regex node type\n";
            exit(EXIT_FAILURE);
        }
    }

  private:
    void print_literal() { std::cout << "Literal(" << value << ")"; }

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

    // left will be used to store the only operand for a kleene's closure
    void print_kleene() {
        std::cout << "KleeneStar(";
        left->print();
        std::cout << ")";
    }
};

/**
 * initialize_nfa - Allocates start and stop state for an nfa.
 */
void initialize_nfa(nfa &n, synthax_cat accept_state_cat = unknown) {
    state start = state{uuid::generate_uuid_v4()};
    n.states[start.name] = start;
    n.start = start.name;

    state accept_state = state{uuid::generate_uuid_v4()};
    n.states[accept_state.name] = accept_state;
    n.accept[accept_state.name] = accept_state_cat;
}

/**
 * e_closure - Takes a set of states, returns a set of states reacheable via
 * only epsilon transitions/closures.
 */
void e_closure(unordered_set<state, state::hash_function> &q,
               unordered_set<state, state::hash_function> &result) {}

/**
 * delta - Applies the transition function to each element of
 * q, given a char c.
 */
void delta_func(unordered_set<state, state::hash_function> &q,
                unordered_set<state, state::hash_function> &result,
                char c) {}

/**
 * nfa_append - Copies states and transitions from one nfa to another
 */
static void nfa_append(nfa &src, nfa &dest) {
    dest.states.insert(src.states.begin(), src.states.end());
    dest.deltas.transitions.insert(
        src.deltas.transitions.begin(),
        src.deltas.transitions.end()
    );
    dest.deltas.epsilon_transitions.insert(
        src.deltas.epsilon_transitions.begin(),
        src.deltas.epsilon_transitions.end()
    );
}

/**
 * add_delta_nfa - Use this function to add a non-epsilon transition to an nfa
 * to maintain a correct sigma set.
 */
static void add_delta_nfa(nfa &nfa, string from_id, string to_id,
                          char character) {
    nfa.deltas.transitions[from_id][character] = to_id;
}

/**
 * full_union_construct - Generates an NFA union construct (a|b) given two nfas.
 * It's a full construct, meaning all accepting states will be mapped to the
 * output.
 *
 *             (New Start State)
 *                    |
 *                   ε|ε
 *                    |
 *              +-----+-----+
 *              |           |
 *              v           v
 *      (Start State of A)  (Start State of B)
 *              |           |
 *             ...         ... (inside layers of A and B)
 *              |           |
 * (A's {Accepting States}) (B's {Accepting States})
 *           \..|           |../
 *              |           |
 *               \         /
 *               ε\       /ε
 *                 v     v
 *           (New Accepting State)
 */
static void full_union_construct(vector<nfa> &src, nfa &result) {
    // Copy state and transitions from a and b to result
    for(auto &n: src) {
        nfa_append(n, result);
        result.deltas.epsilon_transitions[result.start].push_back(n.start);

        for (auto &[acc, cat] : n.accept) {
            for (auto &[res_acc, res_cat] : result.accept)
                result.deltas.epsilon_transitions[acc].push_back(res_acc);
        }
    }
}

/**
 * merge_into_final_nfa - Given nfas for each synthactic category, build a
 * global nfa tha'll be able to recognize any of them.
 *
 * Please pass a dest nfa that has no accept state.
 *
 * Example if |src| = 3
 *                           (dest Start State)
 *                                     |
 *                                    ε|ε
 *                                     |
 *              +-------------+---------------------------------+
 *              |             |                                 |
 *              v             v                                 v
 *    (Start State of A)  (Start State of B)            (Start state of C)
 *              |             |                                 |
 *             ...           ...                               ...
 *              |             |                                 |
 * (A's {Accepting States}) (B's {Accepting States})  (C's {Accepting States})
 */
static void merge_into_final_nfa(vector<nfa> &src, nfa &dest) {
    for (nfa &src_nfa : src) {
        nfa_append(src_nfa, dest);
        dest.deltas.epsilon_transitions[dest.start].push_back(src_nfa.start);
        dest.accept.insert(src_nfa.accept.begin(), src_nfa.accept.end());
    }
}

/**
 * full_concat_construct - Generates an NFA concatenation construct (ab) given
 * two nfas. It's a "full" construct, meaning all accepting states are mapped to
 * the next nfa.
 *
 *   (Start State of A)
 *         |
 *        ...
 *         |
 * ({Accepting States} of A)
 *      \..|../
 *        ε|
 *         |
 *   (Start State of B)
 *         |
 *        ...
 *         |
 *   ({Accepting States} of B)
 */
static void full_concat_construct(vector<nfa> &src, nfa &result) {
    // Copy state and transitions from a and b to result
    result.start = src.begin()->start;
    result.states.clear();
    result.accept.clear();

    for(nfa &n: src) {
        nfa_append(n, result);
        for(auto &[acc,cat]: result.accept) {
            result.deltas.epsilon_transitions[acc].push_back(n.start);
        }
        result.accept = n.accept;
    }
}

/**
 * full_kleene_constuct - Generates an NFA Kleene's closure (a*) construct from
 * an nfa. It's a "full" construct, meaning all accepting states are mapped to
 * the output.
 *
 * In place algorithm.
 *
 *
 *        (New Start State)
 *               |
 *              ε|ε
 *               |
 *         +-----+------------ +
 *         |                   |
 *         v                   |
 *  (Start State of A)         |
 *         |         ^         |
 *        ...        |         |
 *         |         |ε        |
 *         v         |         |
 * ({Accepting States} of A)   |
 *         |\                 /|
 *         | \  ε            / |
 *         |..\             /..|
 *         v   v           v   v
 *        ({New Accepting States)}
 */
static void full_kleene_construct(nfa &a) {
    string old_start;
    unordered_map<string, synthax_cat> old_accept;
    old_start = a.start;
    old_accept = a.accept;
    state new_start = state{uuid::generate_uuid_v4()};
    a.deltas.epsilon_transitions[new_start.name].push_back(old_start);
    state new_accept;
    a.start = new_start.name;
    a.states[new_start.name] = new_start;
    a.accept.clear();

    for (auto &[old_acc, cat]: old_accept){
        new_accept = state{uuid::generate_uuid_v4()};

        a.accept[new_accept.name] = cat;
        a.states[new_accept.name] = new_accept;

        a.deltas.epsilon_transitions[new_start.name].push_back(new_accept.name);

        a.deltas.epsilon_transitions[old_acc].push_back(old_start);
        a.deltas.epsilon_transitions[old_acc].push_back(new_accept.name);
    }
}

nfa create_single_char_nfa(char ch, synthax_cat cat) {
    nfa result;
    initialize_nfa(result, cat);
    result.deltas.transitions[result.start][ch] = result.accept.begin()->first;
    return result;
}

/**
 * char_class_construct - Given a character class, build the NFA to recognize 
 * it.
 *
 * class is 'a-z' format or 'abcds....' format
 *
 */
int char_class_construct(nfa &result, string c)
{
    if (c.size() == 3 && c.at(1) == '-') {
        if(c == "a-z") {
            c = "abcdefghijklmnopqrstuvwxyz";
        } else if(c == "A-Z") {
            c = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        } else if(c == "a-Z") {
            c = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        } else if(c == "0-9") {
            c = "0123456789";
        } else if(c == "1-9") {
            c = "123456789";
        }
    } 
    
    vector<nfa> src;
    for(char &character: c) {
        src.push_back(
            create_single_char_nfa(character, result.accept.begin()->second)
        );
    }

    full_union_construct(src, result);
    return 0;
}

/**
 * literal_construct - Constructs a NFA that can recognize a string/literal 
 * using individual nfa for each char and concatenating them.
 * 
 * Example : literal == "oli"
 *
 *        (New Start State)
 *               |
 *               | "o"
 *               |
 *        (Second State)
 *               |
 *               | ε 
 *               |
 *        (Third State)
 *               |
 *               | "l"
 *               |
 *        (Fourth State)
 *               |
 *               | ε 
 *               |
 *        (Fifth State)
 *               |
 *               | "i"
 *               |
 *        (Accept state)
 *
 */
nfa literal_construct(string literal, synthax_cat cat)
{
    nfa current_char_nfa, prev_char_nfa, result_nfa;
    vector<nfa> src;

    if (literal.empty()) {
        std::cerr << "The literal is empty" << std::endl;
        throw std::invalid_argument("The literal is empty");
    }

    initialize_nfa(result_nfa, cat);

    // Check if literal is a character class (e.g., "[a-z]" or "[abc]")
    if (literal.front() == '[' && literal.back() == ']') {
        string char_class = literal.substr(1, literal.size() - 2);  // Exclude brackets
        char_class_construct(result_nfa, char_class);
    } else {
        //Do the rest
        for(char &c: literal){
            src.push_back(create_single_char_nfa(c, cat));
        }
        full_concat_construct(src, result_nfa);
    }
     
    return result_nfa;
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
int thompson_construction(nfa &n, std::shared_ptr<regex_node> node) {
    if (!node) {
        return EXIT_FAILURE;
    }
    nfa nfa_left, nfa_right;
    vector<nfa> src;

    if (node->variant == 2) {
        initialize_nfa(nfa_left, n.accept.begin()->second);
        initialize_nfa(nfa_right, n.accept.begin()->second);
        thompson_construction(nfa_left, node->left);
        thompson_construction(nfa_right, node->right);
        src.push_back(nfa_left);
        src.push_back(nfa_right);
        full_concat_construct(src, n);
    } else if (node->variant == 1) {
        initialize_nfa(nfa_left, n.accept.begin()->second);
        initialize_nfa(nfa_right, n.accept.begin()->second);
        thompson_construction(nfa_left, node->left);
        thompson_construction(nfa_right, node->right);
        src.push_back(nfa_left);
        src.push_back(nfa_right);
        full_union_construct(src, n);
    } else if (node->variant == 3) {
        initialize_nfa(nfa_left, n.accept.begin()->second);
        thompson_construction(nfa_left, node->left);
        n = nfa_left;
        full_kleene_construct(n);
    } else if (node->variant == 0) {
        n = literal_construct(node->value, n.accept.begin()->second);
    } else {
        cout << "Wrong regex node type" << endl;
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

/**
 * insert_explicit_concat_tokens - Given regexp tokens, insert explicit "."
 * concatenation operators so we can postfix it.
 */
vector<string> insert_explicit_concat_tokens(const vector<string>& tokens) {
    vector<string> result;

    for (size_t i = 0; i < tokens.size(); ++i) {
        result.push_back(tokens[i]);

        if (i + 1 < tokens.size()) {
            string a = tokens[i];
            string b = tokens[i + 1];

            bool aLiteral = (isalnum(a[0]) || a[0] == '[' || a == ")");
            bool bLiteral = (isalnum(b[0]) || b[0] == '[' || b == "(");

            if ((aLiteral && bLiteral) ||
                (aLiteral && b == "(") ||
                (a == ")" && bLiteral) ||
                (a == "*" && bLiteral) ||
                (a == "*" && b == "(") ||
                (a == ")" && b == "(")) {
                result.push_back("·");
            }
        }
    }

    return result;
}

/**
 * re_tokenize - Given a regexp, returns a stream of tokens representing
 * all the elements of the regexp.
 */
static vector<string> re_tokenize(const string &regex) {
    vector<string> tokens;
    string token;
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
        } else if (inClass ||
                   (isalnum(c) && !token.empty() && isalnum(token.back()))) {
            token += c;
        } else {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
            if (c == '(' || c == ')' || c == '|' || c == '*' || c == '\xB7') {
                tokens.push_back(string(1, c));
            } else if (isalnum(c) || c == ';') {
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
static vector<string> re_to_postfix(const vector<string> &tokens) {
    vector<string> output;
    std::stack<string> operators;
    unordered_map<string, int> precedence = { {"*", 3}, {"·", 2}, {"|", 1}};
    unordered_map<string, bool> rightAssociative = {
        {"*", true}, {"·", false}, {"|", false}
    };

    auto isOperator = [&](const string &token) {
        return precedence.find(token) != precedence.end();
    };

    for (const auto &token : tokens) {
        if (isalnum(token[0]) || token == ";" || token == " " ||
            token[0] == '[') {
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
                    (precedence[operators.top()] == precedence[token] &&
                     !rightAssociative[token]))) {
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
static std::shared_ptr<regex_node>
build_thompson_tree(const vector<string> &postfixTokens) {
    std::stack<std::shared_ptr<regex_node>> nodeStack;

    for (const auto &token : postfixTokens) {
        if (token == "*") {
            auto operand = nodeStack.top();
            nodeStack.pop();
            nodeStack.push(
                std::make_shared<regex_node>(3, operand, nullptr, "")
            );
        } else if (token == "|") {
            auto right = nodeStack.top();
            nodeStack.pop();
            auto left = nodeStack.top();
            nodeStack.pop();
            nodeStack.push(std::make_shared<regex_node>(1, left, right, ""));
        } else if (token == "·") {
            auto right = nodeStack.top();
            nodeStack.pop();
            auto left = nodeStack.top();
            nodeStack.pop();
            nodeStack.push(std::make_shared<regex_node>(2, left, right, ""));
        } else {
            // Handle literal or character class
            nodeStack.push(std::make_shared<regex_node>(
                0, nullptr, nullptr,
                token)); // Simplified, assumes token is a valid literal
        }
    }

    return nodeStack.top();
}

// Hash set of states
struct state_set_hash {
    size_t
    operator()(const unordered_set<state, state::hash_function> &s) const {
        string result;
        for (const auto &state : s) {
            result += state.name;
        }
        // Just hash the name field
        return std::hash<string>()(result);
    }
};

// Compare two set of states
struct state_set_pred {
    bool operator()(
        const unordered_set<state, state::hash_function> &s1,
        const unordered_set<state, state::hash_function> &s2) const {
        return s1 == s2;
    }
};

/**
 * Constructs a deterministic finite automaton from a non-deterministic finite
 * automaton.
 */
static void subset_construction(nfa &nfa, dfa &dfa) {
    vector<state> current;
    unordered_set<state, state::hash_function> q0, q, n0_set, t, result;
    unordered_set<
        unordered_set<state, state::hash_function>,
        state_set_hash, state_set_pred> worklist, big_q;

    unordered_map<
        unordered_set<state, state::hash_function>,
        unordered_map<
            char,
            unordered_set<state, state::hash_function>
        >,
        state_set_hash,
        state_set_pred
    > big_t;

    n0_set.insert(nfa.states[nfa.start]);
    e_closure(n0_set, q0);
    big_q.insert(q0);
    worklist.insert(q0);

    while (!worklist.empty()) {
        q.clear();

        // Get an iterator to the first element
        auto it = worklist.begin();
        q = *it;
        // Remove the element from the set
        worklist.erase(q);

        for (auto character : nfa.sigma) {
            result.clear();
            t.clear();
            delta_func(q, result, character);
            e_closure(result, t);

            big_t[q][character] = t;

            if (big_q.count(t) == 0) {
                big_q.insert(t);
                worklist.insert(t);
            }
        }
    }
}

/**
 * minimize_dfa - Remove duplicates states from the dfa using
 * partitionning/segregation
 */
static void minimize_dfa(dfa &dfa) {
    // TODO: Minimize the DFA
}


/**
 * generate_scanner_code() - Generate the scanner code as a file.
 */
static void generate_scanner_code(dfa &glob_dfa) {
    FILE *fp =
        fopen("server/scanner/scanner.cpp", "w"); // Open file in write mode

    if (fp != NULL) {
        string content =
            "#include \"scanner.h\"\n"
            "#include <string>\n\n"
            "/**\n"
            " * lexe - Given a request and a list of tokens allocated on the "
            "heap\n"
            " *\n"
            " */\n"
            "ssize_t lexe(Tokens &tokens, string str) \n"
            "{\n"
            "\tstring state = " +
            glob_dfa.start +
            ";\n"
            "\tswitch(state){\n";

        fprintf(fp, "%s", content.c_str()); // Write content to the file

        for (const auto &[state_uid, state] : glob_dfa.states) {
            string case_statement = "\tcase " + state_uid + ":";
            fprintf(fp, "%s", case_statement.c_str());

            auto it = glob_dfa.accept.find(state_uid);
            if (it != glob_dfa.accept.end()) {
                // The current state is a final step,
                // save the current buffer as maximum munch.
            } else {
                auto next = glob_dfa.deltas.transitions[state_uid];
                for (const auto &[ch, next_state] : next) {
                    string transition = "\t\tif (input == '" + string(1, ch) +
                                        "') state = " + next_state + ";\n";
                    fprintf(fp, "%s", transition.c_str());
                }

                // If program arrives here, it means no transition for current
                // char, try to rollack.
                string rollback = "            rollback();\n";
                fprintf(fp, "%s", rollback.c_str());
            }
        }

        string def = "\tdefault:\n\t\t perror(\"State unknown in the "
                     "DFA\");\n\t\t exit(EXIT_FAILURE);\n";
        string end = "\t}\n    return 0;\n}\n";

        fprintf(fp, "%s", def.c_str()); // Write content to the file
        fprintf(fp, "%s", end.c_str()); // Write content to the file
        fclose(fp);                     // Correct way to close FILE*
    } else {
        printf("Unable to write to the scanner file. Abort\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * construct_scanner() - Build the SQL scanner. Output is an executable and
 * dynamically linkeable file. Run this once offline when modifying the language
 * synthax. Then the file will be used to lexe/tokenize at runtime.
 */
int construct_scanner() {
    nfa int_nfa, key_nfa, op_nfa, endl_nfa, glob_nfa;
    initialize_nfa(int_nfa, integer);
    initialize_nfa(key_nfa, keyword);
    //initialize_nfa(op_nfa, op);
    initialize_nfa(endl_nfa, endline);
    initialize_nfa(glob_nfa, unknown);
    glob_nfa.accept.clear();

    dfa glob_dfa;
    char *code = (char *)malloc(1);

    std::cout << "Building trees of operations for scanner Regexps" << endl;

    auto int_re_tok = re_tokenize(INTEGER_REGEXP);
    auto int_re_tok_w_concat = insert_explicit_concat_tokens(int_re_tok);
    auto int_re_tok_post = re_to_postfix(int_re_tok_w_concat);
    std::shared_ptr<regex_node> int_optree =
        build_thompson_tree(int_re_tok_post);

    auto key_re_tok = re_tokenize(KEYWORD_REGEXP);
    auto key_re_tok_w_concat = insert_explicit_concat_tokens(key_re_tok);
    auto key_re_tok_post = re_to_postfix(key_re_tok_w_concat);
    std::shared_ptr<regex_node> key_optree =
        build_thompson_tree(key_re_tok_post);

    auto endl_re_tok = re_tokenize(END_LINE_REGEXP);
    auto endl_re_tok_w_concat = insert_explicit_concat_tokens(endl_re_tok);
    auto endl_re_tok_post = re_to_postfix(endl_re_tok_w_concat);
    std::shared_ptr<regex_node> endl_optree =
        build_thompson_tree(endl_re_tok_post);

    std::cout << "Tree of operations (INT SCANNER): " << std::endl;
    int_optree->print();
    std::cout << std::endl;
    std::cout << "Tree of operations (KEYWORD SCANNER): " << std::endl;
    key_optree->print();
    std::cout << std::endl;
    std::cout << "Tree of operations (ENDLINE SCANNER): " << std::endl;
    endl_optree->print();
    std::cout << std::endl;

    cout << "Converting INT Optree to nfa" << endl;
    thompson_construction(int_nfa, int_optree);
    cout << "Converting KEYWORD Optree to nfa" << endl;
    thompson_construction(key_nfa, key_optree);
    cout << "Converting ENDLINE Optree to nfa" << endl;
    thompson_construction(endl_nfa, endl_optree);
    
    int_nfa.generate_dot("/tmp/int_nfa.dot");
    key_nfa.generate_dot("/tmp/key_nfa.dot");
    endl_nfa.generate_dot("/tmp/endl_nfa.dot");
    cout << "Merging INT, KEYWORD, ENDLING nfas into a global NFA" << endl;
    vector src = {int_nfa, key_nfa, endl_nfa};
    merge_into_final_nfa(src, glob_nfa);
    cout << "Printing NFA graph into /tmp/nfa.dot for debugging." << endl;
    glob_nfa.generate_dot("/tmp/nfa.dot");

    cout << "Converting Global nfa to dfa" << endl;
    subset_construction(glob_nfa, glob_dfa);
    cout << "Minimizing the dfa" << endl;

    // minimize_dfa(int_dfa);
    cout << "Generate scanner C++ code as a file." << endl;
    generate_scanner_code(glob_dfa);

    free(code);
    return 0;
}

#ifdef TEST
#include <cassert>

int test_full_concat_construct() {
    nfa a, b, result;
    vector<nfa> src;
    initialize_nfa(a, keyword);
    initialize_nfa(b, keyword);
    initialize_nfa(result, keyword);

    auto any_a_acc = a.accept.begin();
    auto any_b_acc = b.accept.begin();
    add_delta_nfa(a, a.start, any_a_acc->first, 'c');
    add_delta_nfa(b, b.start, any_b_acc->first, 'd');
    src.push_back(a);
    src.push_back(b);

    full_concat_construct(src, result);

    assert(result.accept == b.accept);
    assert(result.start == a.start);

    for (auto &[name, cat] : a.accept) {
        assert(result.deltas.epsilon_transitions[name].size() == 1);
    }

    return EXIT_SUCCESS;
}

int test_full_union_construct() {
    nfa a, b, result;
    vector<nfa> src;
    initialize_nfa(a, keyword);
    initialize_nfa(b, keyword);
    initialize_nfa(result, keyword);

    auto any_a_acc = a.accept.begin();
    auto any_b_acc = b.accept.begin();
    add_delta_nfa(a, a.start, any_a_acc->first, 'c');
    add_delta_nfa(b, b.start, any_b_acc->first, 'd');
    
    src.push_back(a);
    src.push_back(b);

    full_union_construct(src, result);

    assert(result.deltas.epsilon_transitions[result.start].size() == 2);

    for (auto &[name, cat] : b.accept) {
        assert(result.deltas.epsilon_transitions[name].size() == 1);
    }
    for (auto &[name, cat] : a.accept) {
        assert(result.deltas.epsilon_transitions[name].size() == 1);
    }
    // TODO: Test all deltas
    return EXIT_SUCCESS;
}

int test_literal_construct() {
    nfa a;
    string literal = "oli";
    a = literal_construct(literal, integer);
    
    assert(a.deltas.transitions[a.start].size() == 1);
    assert(a.deltas.transitions[a.start].begin()->first == 'o');
    assert(a.accept.begin()->second == integer);
    return EXIT_SUCCESS;
}

int test_full_kleene_construct() {
    nfa a;
    initialize_nfa(a, keyword);
    full_kleene_construct(a);

    assert(a.deltas.epsilon_transitions[a.start].size() == 2);
    assert(a.deltas.transitions[a.start].size() == 0);
    return EXIT_SUCCESS;
}

int main() {
    test_full_concat_construct();
    test_full_union_construct();
    test_full_kleene_construct();
    test_literal_construct();
}
#else

int main() { construct_scanner(); }

#endif
