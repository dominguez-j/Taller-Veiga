#ifndef __EQUIPMENT_H__
#define __EQUIPMENT_H__

#include <cstdint>
#include <string>

#include "../server_src/player.h"

struct Equipment {
    uint16_t money = 0;
    bool knife = true;
    std::string primary = "";
    uint16_t primary_ammo = 0;
    std::string secondary = "";
    uint16_t secondary_ammo = 0;

    Equipment() = default;

    explicit Equipment(const Player& p):
            money(p.get_money()),
            knife(p.has_knife()),
            primary(p.get_primary_name()),
            primary_ammo(p.get_primary_ammo()),
            secondary(p.get_secondary_name()),
            secondary_ammo(p.get_secondary_ammo()) {}
};

#endif  //__EQUIPMENT_H__
