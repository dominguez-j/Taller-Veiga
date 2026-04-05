#include "server_protocol.h"

#include <sstream>
#include <vector>

#include "../common_src/buffer.h"
#include "../common_src/converter.h"
#include "../common_src/data.h"
#include "../common_src/parser.h"
#include "../common_src/text_splitter.h"

#define MAX_BUY_REQUEST_SIZE 32

void ServerProtocol::serialize_binary(Equipment&& e) {
    send_uint8_t(Converter::str_to_bin(EQUIPMENT));
    send_uint16_t(htons(static_cast<uint16_t>(e.money)));
    send_uint8_t(static_cast<uint8_t>(e.knife));
    send_uint8_t(Converter::str_to_bin(e.primary));
    send_uint16_t(htons(static_cast<uint16_t>(e.primary_ammo)));
    send_uint8_t(Converter::str_to_bin(e.secondary));
    send_uint16_t(htons(static_cast<uint16_t>(e.secondary_ammo)));
}

void ServerProtocol::serialize_text(Equipment&& e) {
    std::string cmd = Converter::cmd_translation(EQUIPMENT);
    std::stringstream ss;

    ss << cmd << "money:" << e.money << END_OF_LINE;
    ss << cmd << "knife:" << (e.knife ? "true" : "false") << END_OF_LINE;
    ss << cmd << "primary:" << e.primary << COMMA << e.primary_ammo << END_OF_LINE;
    ss << cmd << "secondary:" << e.secondary << COMMA << e.secondary_ammo << END_OF_LINE;

    send_string(ss.str());
}

BuyRequest ServerProtocol::deserialize_binary() {
    BuyRequest buy_request;
    buy_request.command = Converter::bin_to_cmd(recv_uint8_t());

    if (buy_request.command == BUY) {
        buy_request.weapon_name = Converter::bin_to_weapon(recv_uint8_t());
    } else {
        buy_request.weapon_type = Converter::bin_to_weapon_type(recv_uint8_t());
        buy_request.ammo_count = ntohs(recv_uint16_t());
    }
    return buy_request;
}

BuyRequest ServerProtocol::deserialize_text() {
    std::string message;
    Buffer buffer(MAX_BUY_REQUEST_SIZE);
    int end_of_line = 0;
    while (end_of_line == 0) {
        std::string received = recv_some_string(buffer.size());
        if (received.empty()) {
            throw std::runtime_error("Connection closed by client");
        }

        if (received.back() == END_OF_LINE)
            end_of_line = 1;

        message.append(received);
    }
    return Parser::parse_buy_request_from_server(message);
}

void ServerProtocol::send_equipment(Equipment&& e) {
    type_of_protocol == BINARY ? serialize_binary(std::move(e)) : serialize_text(std::move(e));
}

BuyRequest ServerProtocol::receive_buy_request() {
    return type_of_protocol == BINARY ? deserialize_binary() : deserialize_text();
}

void ServerProtocol::send_protocol() {
    send_uint8_t(Converter::str_to_bin("protocol"));
    send_uint8_t(Converter::str_to_bin(type_of_protocol));
}

std::string ServerProtocol::receive_username() {
    recv_uint8_t();  // Drop
    return recv_string(recv_uint16_t());
}
