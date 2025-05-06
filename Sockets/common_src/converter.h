#ifndef __CONVERTER_H__
#define __CONVERTER_H__

#include <cstdint>
#include <map>
#include <string>

class Converter {
public:
    static uint8_t str_to_bin(const std::string& s);
    static std::string bin_to_weapon(uint8_t weapon_bin);
    static std::string bin_to_weapon_type(uint8_t weapon_type_bin);
    static std::string bin_to_cmd(uint8_t cmd_bin);
    static std::string bin_to_protocol(uint8_t protocol_bin);
    static std::string cmd_translation(const std::string& cmd);
    static std::string weapon_to_type(const std::string& weapon_name);

private:
    static const std::map<std::string, uint8_t> str_to_bin_map;
    static const std::map<uint8_t, std::string> bin_to_weapon_map;
    static const std::map<uint8_t, std::string> bin_to_weapon_type_map;
    static const std::map<uint8_t, std::string> bin_to_cmd_map;
    static const std::map<uint8_t, std::string> bin_to_protocol_map;
    static const std::map<std::string, std::string> cmd_translation_map;
    static const std::map<std::string, std::string> weapon_to_type_map;
};

#endif  // __CONVERTER_H__
