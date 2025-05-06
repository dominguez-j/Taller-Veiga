#include "converter.h"

#include "data.h"

const std::map<std::string, uint8_t> Converter::str_to_bin_map = {
        {NOT_EQUIPPED, 0x00}, {GLOCK, 0x01},    {AK47, 0x02},      {M3, 0x03},
        {AWP, 0x04},          {PRIMARY, 0x01},  {SECONDARY, 0x02}, {BINARY, 0x07},
        {TEXT, 0x08},         {USERNAME, 0x01}, {BUY, 0x02},       {AMMO, 0x3},
        {"protocol", 0x06},   {EQUIPMENT, 0x07}};

const std::map<uint8_t, std::string> Converter::bin_to_weapon_map = {
        {0x00, NOT_EQUIPPED}, {0x01, GLOCK}, {0x02, AK47}, {0x03, M3}, {0x04, AWP}};

const std::map<uint8_t, std::string> Converter::bin_to_weapon_type_map = {{0x01, PRIMARY},
                                                                          {0x02, SECONDARY}};

const std::map<uint8_t, std::string> Converter::bin_to_cmd_map = {
        {0x01, USERNAME}, {0x02, BUY}, {0x03, AMMO}, {0x07, EQUIPMENT}};

const std::map<uint8_t, std::string> Converter::bin_to_protocol_map = {{0x07, BINARY},
                                                                       {0x08, TEXT}};

const std::map<std::string, std::string> Converter::cmd_translation_map = {
        {BUY, "buy.weapon"}, {AMMO, "buy.ammo"}, {EQUIPMENT, "equipment."},
        {"buy.weapon", BUY}, {"buy.ammo", AMMO}, {"equipment.", EQUIPMENT}};

const std::map<std::string, std::string> Converter::weapon_to_type_map = {
        {GLOCK, SECONDARY}, {AK47, PRIMARY}, {M3, PRIMARY}, {AWP, PRIMARY}};

uint8_t Converter::str_to_bin(const std::string& s) { return str_to_bin_map.at(s); }

std::string Converter::bin_to_weapon(uint8_t weapon_bin) {
    return bin_to_weapon_map.at(weapon_bin);
}

std::string Converter::bin_to_weapon_type(uint8_t weapon_type_bin) {
    return bin_to_weapon_type_map.at(weapon_type_bin);
}

std::string Converter::bin_to_cmd(uint8_t cmd_bin) { return bin_to_cmd_map.at(cmd_bin); }

std::string Converter::bin_to_protocol(uint8_t protocol_bin) {
    return bin_to_protocol_map.at(protocol_bin);
}

std::string Converter::cmd_translation(const std::string& cmd) {
    return cmd_translation_map.at(cmd);
}

std::string Converter::weapon_to_type(const std::string& weapon_name) {
    return weapon_to_type_map.at(weapon_name);
}
