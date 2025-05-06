#ifndef __EQUIPMENT_H__
#define __EQUIPMENT_H__

#include <cstdint>
#include <string>

struct Equipment {
    uint16_t money;
    bool knife;
    std::string primary;
    uint16_t primary_ammo;
    std::string secondary;
    uint16_t secondary_ammo;

    Equipment():
            money(0), knife(true), primary(""), primary_ammo(0), secondary(""), secondary_ammo(0) {}
};

#endif  //__EQUIPMENT_H__
