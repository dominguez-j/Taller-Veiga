#include "client_protocol.h"

#include <utility>

#include <netinet/in.h>

#include "../common_src/buffer.h"
#include "../common_src/converter.h"
#include "../common_src/data.h"
#include "../common_src/parser.h"
#include "../common_src/text_splitter.h"

#define MAX_EQUIPMENT_SIZE 128
#define MAX_ENDL 4

void ClientProtocol::serialize_binary(BuyRequest&& buy_request) {
    uint8_t cmd_code = Converter::str_to_bin(buy_request.command);
    skt.sendall(&cmd_code, sizeof(cmd_code));

    if (buy_request.command == BUY) {
        uint8_t weapon_code = Converter::str_to_bin(buy_request.weapon_name);
        skt.sendall(&weapon_code, sizeof(weapon_code));
    } else {
        uint8_t weapon_type = Converter::str_to_bin(buy_request.weapon_type);
        uint16_t ammo_count = htons(static_cast<uint16_t>(buy_request.ammo_count));

        skt.sendall(&weapon_type, sizeof(weapon_type));
        skt.sendall(&ammo_count, sizeof(ammo_count));
    }
}

void ClientProtocol::serialize_text(BuyRequest&& buy_request) {
    std::stringstream ss;
    std::string cmd = Converter::cmd_translation(buy_request.command);

    ss << cmd;
    if (buy_request.command == BUY)
        ss << COLON << buy_request.weapon_name;
    else
        ss << DOT << buy_request.weapon_type << COLON << buy_request.ammo_count;

    ss << END_OF_LINE;
    skt.sendall(ss);
}

Equipment ClientProtocol::deserialize_binary(bool& connected) {
    Equipment e;
    uint8_t cmd, knife, primary, secondary;
    uint16_t money, primary_ammo, secondary_ammo;

    skt.recvall(&cmd, sizeof(cmd));
    skt.recvall(&money, sizeof(money));
    skt.recvall(&knife, sizeof(knife));
    skt.recvall(&primary, sizeof(primary));
    skt.recvall(&primary_ammo, sizeof(primary_ammo));
    skt.recvall(&secondary, sizeof(secondary));
    connected = skt.recvall(&secondary_ammo, sizeof(secondary_ammo));
    if (!connected)
        return Equipment();

    e.money = ntohs(money);
    e.knife = static_cast<bool>(knife);
    e.primary = Converter::bin_to_weapon(primary);
    e.primary_ammo = ntohs(primary_ammo);
    e.secondary = Converter::bin_to_weapon(secondary);
    e.secondary_ammo = ntohs(secondary_ammo);

    return e;
}

Equipment ClientProtocol::deserialize_text(bool& connected) {
    std::string message;
    Buffer buffer(MAX_EQUIPMENT_SIZE);
    int count_endl = 0;
    while (count_endl < MAX_ENDL) {
        int bytes_received = skt.recvsome(buffer.data(), buffer.size());
        if (bytes_received == 0) {
            connected = false;
            return Equipment();
        }

        for (int i = 0; i < bytes_received; i++) {
            if (buffer[i] == END_OF_LINE)
                count_endl++;
        }
        message.append(buffer.data(), bytes_received);
    }

    return Parser::parse_equipment_from_client(message);
}

void ClientProtocol::send_buy_request(BuyRequest&& buy_request) {
    type_of_protocol == BINARY ? serialize_binary(std::move(buy_request)) :
                                 serialize_text(std::move(buy_request));
}

Equipment ClientProtocol::receive_equipment(bool& connected) {
    return type_of_protocol == BINARY ? deserialize_binary(connected) : deserialize_text(connected);
}

void ClientProtocol::receive_protocol() {
    uint8_t cmd, protocol;
    skt.recvall(&cmd, sizeof(cmd));
    skt.recvall(&protocol, sizeof(protocol));
    type_of_protocol = Converter::bin_to_protocol(protocol);
}

void ClientProtocol::send_username(const std::string& username) {
    uint8_t cmd = Converter::str_to_bin(USERNAME);
    uint16_t username_size = htons(username.size());
    skt.sendall(&cmd, sizeof(cmd));
    skt.sendall(&username_size, sizeof(username_size));
    skt.sendall(username.c_str(), username.size());
}
