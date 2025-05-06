#ifndef CONVERTER_H
#define CONVERTER_H

#include <cstdint>
#include <map>
#include <string>

#include "constants.h"

class Converter {
private:
    const std::map<std::string, uint8_t> cmd_to_bin_map;
    const std::map<uint8_t, std::string> bin_to_cmd_map;

    Converter(const Converter&) = delete;
    Converter& operator=(const Converter&) = delete;

public:
    Converter():
            cmd_to_bin_map({{CREAR, 0x6E}, {LISTAR, 0x6C}, {UNIRSE, 0x6A}, {JUGAR, 0x70}}),
            bin_to_cmd_map({{0x6E, CREAR}, {0x6C, LISTAR}, {0x6A, UNIRSE}, {0x70, JUGAR}}) {}

    uint8_t cmd_to_bin(const std::string& s) const;
    std::string bin_to_cmd(const uint8_t& b) const;


    Converter(Converter&&) = default;
    Converter& operator=(Converter&&) = default;

    ~Converter() = default;
};

#endif  // CONVERTER_H
