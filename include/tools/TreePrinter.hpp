#ifndef TREE_PRINTER_HPP
#define TREE_PRINTER_HPP

#include <algorithm>
#include <ostream>
#include <string>
#include "../../external/mutable_array_sequence.h"

void print_tree_levels(std::ostream& out, const mutable_array_sequence<mutable_array_sequence<std::string>>& levels) {
    if (levels.get_length() == 0) return;
    std::size_t cell = 4;
    for (int depth = 0; depth < levels.get_length(); ++depth) {
        for (int i = 0; i < levels[depth].get_length(); ++i) {
            cell = std::max(cell, levels[depth][i].size() + 2);
        }
    }
    std::size_t width = cell * levels.get_last().get_length();
    for (std::size_t depth = 0; depth < static_cast<std::size_t>(levels.get_length()); ++depth) {
        std::size_t step = width / static_cast<std::size_t>(levels[depth].get_length());
        std::size_t printed = 0;
        for (std::size_t i = 0; i < static_cast<std::size_t>(levels[depth].get_length()); ++i) {
            const std::string& value = levels[depth][i];
            if (value.empty()) continue;
            std::size_t start = i * step + step / 2 - value.size() / 2;
            out << std::string(start - printed, ' ') << value;
            printed = start + value.size();
        }
        out << '\n';
        if (depth + 1 == static_cast<std::size_t>(levels.get_length())) break;

        std::string branches(width, ' ');
        for (std::size_t i = 0; i < static_cast<std::size_t>(levels[depth].get_length()); ++i) {
            if (!levels[depth + 1][2*i].empty()) branches[i*step + 3*step/8] = '/';
            if (!levels[depth + 1][2*i+1].empty()) branches[i*step + 5*step/8] = '\\';
        }
        out << branches << '\n';
    }
}

#endif // TREE_PRINTER_HPP
