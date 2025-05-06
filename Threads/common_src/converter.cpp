#include "converter.h"

#include "constants.h"

uint8_t Converter::cmd_to_bin(const std::string& s) const { return cmd_to_bin_map.at(s); }

std::string Converter::bin_to_cmd(const uint8_t& b) const { return bin_to_cmd_map.at(b); }
