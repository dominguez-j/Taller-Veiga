#include "ss_formatter.h"

std::stringstream SSFormatter::format_table(const Board& table, const std::string& message) const {
    std::stringstream ss;
    ss << "    " << 1 << " . " << 2 << " . " << 3 << " .\n";
    ss << "  "
       << "+---+---+---+\n";
    ss << "1"
       << " | " << table.get_cell(0, 0) << " | " << table.get_cell(0, 1) << " | "
       << table.get_cell(0, 2) << " |\n";
    ss << "  "
       << "+---+---+---+\n";
    ss << "2"
       << " | " << table.get_cell(1, 0) << " | " << table.get_cell(1, 1) << " | "
       << table.get_cell(1, 2) << " |\n";
    ss << "  "
       << "+---+---+---+\n";
    ss << "3"
       << " | " << table.get_cell(2, 0) << " | " << table.get_cell(2, 1) << " | "
       << table.get_cell(2, 2) << " |\n";
    ss << "  "
       << "+---+---+---+\n";
    if (!message.empty())
        ss << message;
    return ss;
}

std::stringstream SSFormatter::format_party_list(
        const std::vector<std::string>& party_names) const {
    std::stringstream ss;
    ss << "Partidas:\n";
    for (size_t i = 0; i < party_names.size(); i++) ss << " - " << party_names[i] << "\n";

    return ss;
}
