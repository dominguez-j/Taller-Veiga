#include "server.h"

#include <utility>

#include "../common_src/buy_request.h"
#include "../common_src/data.h"
#include "../common_src/equipment.h"
#include "../common_src/printer.h"

#include "shop.h"
#include "weapon.h"

void Server::create_player() {
    std::string username = protocol.receive_username();
    welcome_message(username);
    player.set_username(username);
}

void Server::welcome_message(const std::string& username) const {
    Printer::print("Welcome " + username + "!\n");
}

void Server::send_protocol() { protocol.send_protocol(); }

BuyRequest Server::receive_buy_request() { return protocol.receive_buy_request(); }

void Server::send_player_equipment() { protocol.send_equipment(std::move(Equipment(player))); }

void Server::run() {
    create_player();
    send_protocol();
    send_player_equipment();
    while (true) {
        Shop::try_purchase(std::move(receive_buy_request()), player);
        send_player_equipment();
    }
}
