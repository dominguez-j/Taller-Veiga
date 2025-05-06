#ifndef __BUY_REQUEST_H__
#define __BUY_REQUEST_H__

#include <string>

struct BuyRequest {
    std::string command;
    std::string weapon_name;
    std::string weapon_type;
    int ammo_count;

    BuyRequest(): command(""), weapon_name(""), weapon_type(""), ammo_count(0) {}
};

#endif  //__BUY_REQUEST_H__
