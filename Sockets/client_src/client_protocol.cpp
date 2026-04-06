#include "client_protocol.h"

#include <algorithm>
#include <utility>

#include "../common_src/buffer.h"
#include "../common_src/converter.h"
#include "../common_src/data.h"
#include "../common_src/parser.h"
#include "../common_src/text_splitter.h"

#define MAX_EQUIPMENT_SIZE 128
#define MAX_ENDL 4

void ClientProtocol::serialize_binary(BuyRequest&& buy_request) {
    send_uint8_t(Converter::str_to_bin(buy_request.command));

    if (buy_request.command == BUY) {
        send_uint8_t(Converter::str_to_bin(buy_request.weapon_name));
    } else {
        send_uint8_t(Converter::str_to_bin(buy_request.weapon_type));
        send_uint16_t(static_cast<uint16_t>(buy_request.ammo_count));
    }
}

void ClientProtocol::serialize_text(BuyRequest&& buy_request) {
    std::string txt = Converter::cmd_translation(buy_request.command);

    if (buy_request.command == BUY)
        txt += COLON + buy_request.weapon_name;
    else
        txt += DOT + buy_request.weapon_type + COLON + std::to_string(buy_request.ammo_count);

    txt += END_OF_LINE;
    send_string(txt);
}

Equipment ClientProtocol::deserialize_binary() {
    Equipment e;
    recv_uint8_t();  // Drop

    e.money = recv_uint16_t();
    e.knife = static_cast<bool>(recv_uint8_t());
    e.primary = Converter::bin_to_weapon(recv_uint8_t());
    e.primary_ammo = recv_uint16_t();
    e.secondary = Converter::bin_to_weapon(recv_uint8_t());
    e.secondary_ammo = recv_uint16_t();

    return e;
}

Equipment ClientProtocol::deserialize_text() {
    std::string message;
    int count_endl = 0;
    while (count_endl < MAX_ENDL) {
        std::string received = recv_some_string(MAX_EQUIPMENT_SIZE);
        if (received.empty()) {
            throw std::runtime_error("Connection closed by server");
        }

        count_endl += std::count(received.begin(), received.end(), END_OF_LINE);
        message.append(received);
    }

    return Parser::parse_equipment_from_client(message);
}

void ClientProtocol::send_buy_request(BuyRequest&& buy_request) {
    type_of_protocol == BINARY ? serialize_binary(std::move(buy_request)) :
                                 serialize_text(std::move(buy_request));
}

Equipment ClientProtocol::receive_equipment() {
    return type_of_protocol == BINARY ? deserialize_binary() : deserialize_text();
}

void ClientProtocol::receive_protocol() {
    recv_uint8_t();  // Drop
    type_of_protocol = Converter::bin_to_protocol(recv_uint8_t());
}

void ClientProtocol::send_username(const std::string& username) {
    send_uint8_t(Converter::str_to_bin(USERNAME));
    send_uint16_t(username.size());
    send_string(username);
}
