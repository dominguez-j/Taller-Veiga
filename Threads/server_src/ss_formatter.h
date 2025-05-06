#ifndef SS_FORMATTER_H
#define SS_FORMATTER_H

#include <sstream>
#include <string>
#include <vector>

#include "board.h"

class SSFormatter {
private:
    SSFormatter(const SSFormatter&) = delete;
    SSFormatter& operator=(const SSFormatter&) = delete;

public:
    SSFormatter() = default;

    std::stringstream format_table(const Board& table, const std::string& message) const;
    std::stringstream format_party_list(const std::vector<std::string>& party_names) const;

    SSFormatter(SSFormatter&&) = default;
    SSFormatter& operator=(SSFormatter&&) = default;

    ~SSFormatter() = default;
};

#endif  // SS_FORMATTER_H
