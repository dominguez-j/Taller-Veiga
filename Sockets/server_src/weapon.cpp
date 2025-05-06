#include "weapon.h"

int Weapon::get_ammo_count() const { return ammo_count; }

void Weapon::add_bullets(int bullets) { ammo_count += bullets; }

std::string Weapon::get_name() const { return name; }
