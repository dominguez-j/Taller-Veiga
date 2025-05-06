#include "server_protocol.h"

#include <sstream>
#include <vector>

#include <netinet/in.h>

#include "../common_src/buffer.h"
#include "../common_src/converter.h"
#include "../common_src/data.h"
#include "../common_src/parser.h"
#include "../common_src/text_splitter.h"

#define MAX_BUY_REQUEST_SIZE 32

void ServerProtocol::serialize_binary(Equipment&& e) {
    uint8_t cmd = Converter::str_to_bin(EQUIPMENT);
    uint16_t money = htons(static_cast<uint16_t>(e.money));
    uint8_t knife = static_cast<uint8_t>(e.knife);
    uint8_t primary = Converter::str_to_bin(e.primary);
    uint16_t primary_ammo = htons(static_cast<uint16_t>(e.primary_ammo));
    uint8_t secondary = Converter::str_to_bin(e.secondary);
    uint16_t secondary_ammo = htons(static_cast<uint16_t>(e.secondary_ammo));

    peer.sendall(&cmd, sizeof(cmd));
    peer.sendall(&money, sizeof(money));
    peer.sendall(&knife, sizeof(knife));
    peer.sendall(&primary, sizeof(primary));
    peer.sendall(&primary_ammo, sizeof(primary_ammo));
    peer.sendall(&secondary, sizeof(secondary));
    peer.sendall(&secondary_ammo, sizeof(secondary_ammo));
}

void ServerProtocol::serialize_text(Equipment&& e) {
    std::string cmd = Converter::cmd_translation(EQUIPMENT);
    std::stringstream ss;

    ss << cmd << "money:" << e.money << END_OF_LINE;
    ss << cmd << "knife:" << (e.knife ? "true" : "false") << END_OF_LINE;
    ss << cmd << "primary:" << e.primary << COMMA << e.primary_ammo << END_OF_LINE;
    ss << cmd << "secondary:" << e.secondary << COMMA << e.secondary_ammo << END_OF_LINE;

    peer.sendall(ss);
}

BuyRequest ServerProtocol::deserialize_binary(bool& connected) {
    uint8_t cmd;
    BuyRequest buy_request;
    connected = peer.recvall(&cmd, sizeof(cmd));
    if (!connected)
        return BuyRequest();

    buy_request.command = Converter::bin_to_cmd(cmd);

    if (buy_request.command == BUY) {
        uint8_t weapon_code;

        connected = peer.recvall(&weapon_code, sizeof(weapon_code));
        if (!connected)
            return BuyRequest();

        buy_request.weapon_name = Converter::bin_to_weapon(weapon_code);
    } else {
        uint8_t weapon_type;
        uint16_t ammo_count;

        peer.recvall(&weapon_type, sizeof(weapon_type));
        connected = peer.recvall(&ammo_count, sizeof(ammo_count));
        if (!connected)
            return BuyRequest();

        buy_request.weapon_type = Converter::bin_to_weapon_type(weapon_type);
        buy_request.ammo_count = ntohs(ammo_count);
    }
    return buy_request;
}

BuyRequest ServerProtocol::deserialize_text(bool& connected) {
    std::string message;
    Buffer buffer(MAX_BUY_REQUEST_SIZE);
    int end_of_line = 0;
    while (end_of_line == 0) {
        int bytes_received = peer.recvsome(buffer.data(), buffer.size());
        if (bytes_received == 0) {
            connected = false;
            return BuyRequest();
        }

        if (buffer[bytes_received - 1] == END_OF_LINE)
            end_of_line = 1;

        message.append(buffer.data(), bytes_received - end_of_line);
    }
    return Parser::parse_buy_request_from_server(message);
}

void ServerProtocol::send_equipment(Equipment&& e) {
    type_of_protocol == BINARY ? serialize_binary(std::move(e)) : serialize_text(std::move(e));
}

BuyRequest ServerProtocol::receive_buy_request(bool& connected) {
    return type_of_protocol == BINARY ? deserialize_binary(connected) : deserialize_text(connected);
}

void ServerProtocol::send_protocol() {
    uint8_t cmd = Converter::str_to_bin("protocol");
    uint8_t protocol = Converter::str_to_bin(type_of_protocol);
    peer.sendall(&cmd, sizeof(cmd));
    peer.sendall(&protocol, sizeof(protocol));
}

std::string ServerProtocol::receive_username() {
    uint8_t cmd;
    uint16_t username_size;

    peer.recvall(&cmd, sizeof(cmd));
    peer.recvall(&username_size, sizeof(username_size));
    username_size = ntohs(username_size);

    Buffer user(username_size);
    peer.recvall(user.data(), user.size());
    return std::string(user.data(), user.size());
}
