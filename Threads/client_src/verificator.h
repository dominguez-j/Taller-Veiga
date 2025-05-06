#ifndef VERIFICATOR_H
#define VERIFICATOR_H

#include <set>
#include <string>

#include "../common_src/constants.h"

#include "text_splitter.h"

class Verificator {
private:
    TextSplitter txt_splitter;
    std::set<std::string> valid_commands;

    Verificator(const Verificator&) = delete;
    Verificator& operator=(const Verificator&) = delete;

public:
    Verificator(): valid_commands({CREAR, LISTAR, UNIRSE, JUGAR}) {}

    const bool verificate_operation(const std::string& message);

    Verificator(Verificator&&) = default;
    Verificator& operator=(Verificator&&) = default;
};

#endif  // VERIFICATOR_H
