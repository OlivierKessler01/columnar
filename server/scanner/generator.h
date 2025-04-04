#pragma once

#include <fstream>
#include <iostream>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct state {
    string name;

    // Overload the comparison operator, used to lookup in state sets
    bool operator==(const state &other_state) const {
        if (this->name == other_state.name) {
            return true;
        } else
            return false;
    }

    // Used to hash states into sets
    struct hash_function {
        size_t operator()(const state &state) const {
            return std::hash<string>()(state.name);
        }
    };
};

struct deltas_t {
    // [start_state_id[char] -> stop_state_name]
    unordered_map<string, unordered_map<char, string>> transitions;
    // [start_state_id -> ...stop_state_names]
    unordered_map<string, std::vector<string>> epsilon_transitions;
};

enum synthax_cat {
    keyword = 0,
    whitespace = 1,
    integer = 2,
    identifier = 3,
    comment = 4,
    op = 5,
    endline = 6,
};

struct nfa {
  public:
    void generate_dot(const string &filename) const;
    string start;
    unordered_map<string, synthax_cat> accept; // accepting states
    unordered_set<char> sigma;                 // finite alphabet used by the nfa
    unordered_map<string, state> states;       // [state_uid -> state...]
    deltas_t deltas;
};

struct dfa {
    string start;
    unordered_map<string, synthax_cat> accept; // accepting states
    unordered_set<char> sigma;           // finite alphabet used by the nfa
    unordered_map<string, state> states; // [state_uid -> state...]
    deltas_t deltas;                     // [state_uid -> deltas...]
};

string synthax_cat_to_string(synthax_cat category);
