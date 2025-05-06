#ifndef PARSER_H
#define PARSER_H

#include <string>

#include "../common_src/client_command.h"

#include "text_splitter.h"

class Parser {
private:
    TextSplitter txt_splitter;

    Parser(const Parser&) = delete;
    Parser& operator=(const Parser&) = delete;

public:
    Parser() = default;

    ClientCommand parse_client_command(const std::string& command);

    Parser(Parser&&) = default;
    Parser& operator=(Parser&&) = default;

    ~Parser() = default;
};

#endif  // PARSER_H
