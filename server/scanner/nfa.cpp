#include "generator.h"

string synthax_cat_to_string(synthax_cat category) {
    switch (category) {
    case keyword:
        return "keyword";
    case whitespace:
        return "whitespace";
    case integer:
        return "integer";
    case identifier:
        return "identifier";
    case comment:
        return "comment";
    default:
        return "unknown";
    }
}

void nfa::generate_dot(const string &filename) const {
    ofstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    file << "digraph NFA {\n";
    file << "    rankdir=LR;\n";
    file << "    node [shape=circle];\n";

    // Accepting states
    for (const auto &[state, category] : accept) {
        file << "    \"" << synthax_cat_to_string(category)
             << "\" [shape=doublecircle];\n";
    }

    // Start state arrow
    file << "    " << "start"
         << " [shape=none, label=\""
            "\" ];\n";
    file << "    start -> \"" << start << "\";\n";

    // Normal transitions
    for (const auto &[from, edges] : deltas.transitions) {
        for (const auto &[symbol, to] : edges) {
            file << "    \"" << from << "\" -> \"" << to << "\" [label=\""
                 << symbol << "\"];\n";
        }
    }

    // Epsilon transitions
    for (const auto &[from, to_list] : deltas.epsilon_transitions) {
        for (const auto &to : to_list) {
            file << "    \"" << from << "\" -> \"" << to
                 << "\" [label=\"ε\", style=dashed];\n";
        }
    }

    file << "}\n";
    file.close();
    cout << "DOT file generated: " << filename << endl;
}
