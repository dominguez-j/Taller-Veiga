#include "player.h"

#include <utility>

#include "../common_src/converter.h"
#include "../common_src/data.h"

bool Player::has_knife() const { return knife; }
int Player::get_money() const { return money; }

void Player::update_money(int amount) { money += amount; }

void Player::set_ammo_weapon(const std::string& weapon_to_type, int num_ammo) {
    if (weapon_to_type == PRIMARY)
        primary.add_bullets(num_ammo);
    else
        secondary.add_bullets(num_ammo);
}

void Player::set_weapon(const std::string& weapon) {
    if (Converter::weapon_to_type(weapon) == PRIMARY)
        primary = std::move(Weapon(weapon));
    else
        secondary = std::move(Weapon(weapon));
}

std::string Player::get_primary_name() const { return primary.get_name(); }
std::string Player::get_secondary_name() const { return secondary.get_name(); }
int Player::get_primary_ammo() const { return primary.get_ammo_count(); }
int Player::get_secondary_ammo() const { return secondary.get_ammo_count(); }
