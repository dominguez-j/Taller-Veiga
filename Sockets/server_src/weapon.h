#ifndef __WEAPON_H__
#define __WEAPON_H__

#include <string>

#include "../common_src/data.h"

class Weapon {
private:
    int ammo_count;
    std::string name;

    Weapon(const Weapon&) = delete;
    Weapon& operator=(const Weapon&) = delete;

public:
    explicit Weapon(const std::string& name): name(name) {
        if (name == NOT_EQUIPPED)
            ammo_count = 0;
        else
            ammo_count = 30;
    }

    int get_ammo_count() const;
    void add_bullets(int bullets);
    std::string get_name() const;

    Weapon(Weapon&&) = default;
    Weapon& operator=(Weapon&&) = default;

    ~Weapon() = default;
};

#endif  // __WEAPON_H__
