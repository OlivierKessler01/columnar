#pragma once

#include <iostream>
#include <random>
#include <set>
#include <sstream>
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

struct nfa {
    string start;
    std::vector<string> accept;               // accepting states
    unordered_set<char> sigma;           // finite alphabet used by the nfa
    unordered_map<string, state> states; // [state_uid -> state...]
    deltas_t deltas;
};

struct dfa {
    string start;
    std::vector<string> accept;
    deltas_t deltas; // [state_uid -> deltas...]
};

enum synthax_cat {
    keyword = 0,
    whitespace = 1,
    integer = 2,
    identifier = 3,
    comment = 4,
};
