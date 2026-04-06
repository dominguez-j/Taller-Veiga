#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>

#include "weapon.h"

#define STARTING_MONEY 500

class Player {
private:
    std::string username = "";
    Weapon primary = Weapon(NOT_EQUIPPED);
    Weapon secondary = Weapon(GLOCK);
    bool knife = true;
    int money = STARTING_MONEY;

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

public:
    Player() = default;

    int get_money() const;
    void update_money(int amount);
    bool has_knife() const;
    void set_weapon(const std::string& weapon);
    void set_ammo_weapon(const std::string& weapon_name, int num_ammo);
    void set_username(const std::string& name);
    std::string get_primary_name() const;
    std::string get_secondary_name() const;
    int get_primary_ammo() const;
    int get_secondary_ammo() const;

    Player(Player&&) = default;
    Player& operator=(Player&&) = default;

    ~Player() = default;
};

#endif  // __PLAYER_H__
