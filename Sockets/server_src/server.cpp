#include "server.h"

#include <iostream>
#include <utility>

#include "../common_src/buy_request.h"
#include "../common_src/data.h"
#include "../common_src/equipment.h"
#include "../common_src/text_splitter.h"

#include "shop.h"
#include "weapon.h"

void Server::create_player() {
    std::string username = protocol.receive_username();
    player = std::move(Player(username));
    welcome_message(username);
}

void Server::welcome_message(const std::string& username) const {
    std::cout << username << " has arrived!" << std::endl;
}

void Server::send_protocol() { protocol.send_protocol(); }

BuyRequest Server::receive_buy_request(bool& connected) {
    return protocol.receive_buy_request(connected);
}

void Server::send_player_equipment() {
    Equipment e;

    e.money = player.get_money();
    e.knife = player.has_knife();
    e.primary = player.get_primary_name();
    e.primary_ammo = player.get_primary_ammo();
    e.secondary = player.get_secondary_name();
    e.secondary_ammo = player.get_secondary_ammo();

    protocol.send_equipment(std::move(e));
}

void Server::run() {
    create_player();
    send_protocol();
    send_player_equipment();
    bool connected = true;
    while (connected) {
        BuyRequest buy_request = receive_buy_request(connected);
        if (connected) {
            Shop::try_purchase(std::move(buy_request), player);
            send_player_equipment();
        }
    }
}
