#include "shop.h"

#include <iostream>

#include "../common_src/data.h"

#define WEAPON_COST 100
#define AMMO_COST 1

void Shop::print_purchase_failed(const std::string& cmd) {
    std::cout << "Not enough money to buy " << (cmd == BUY ? WEAPON : AMMO) << std::endl;
}

void Shop::try_purchase(BuyRequest&& buy_request, Player& player) {
    if (buy_request.command == BUY) {

        if (player.get_primary_name() == buy_request.weapon_name or
            player.get_secondary_name() == buy_request.weapon_name) {
            return;
        }

        if (player.get_money() < WEAPON_COST) {
            print_purchase_failed(buy_request.command);
            return;
        }

        player.update_money(-WEAPON_COST);
        player.set_weapon(buy_request.weapon_name);
    } else if (buy_request.command == AMMO) {
        if ((buy_request.weapon_type == PRIMARY and player.get_primary_name() == NOT_EQUIPPED) or
            (buy_request.weapon_type == SECONDARY and
             player.get_secondary_name() == NOT_EQUIPPED)) {
            return;
        }

        int total_cost = AMMO_COST * buy_request.ammo_count;
        if (player.get_money() < total_cost) {
            print_purchase_failed(buy_request.command);
            return;
        }

        player.update_money(-total_cost);
        player.set_ammo_weapon(buy_request.weapon_type, buy_request.ammo_count);
    }
}
