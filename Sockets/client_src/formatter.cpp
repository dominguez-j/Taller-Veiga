#include "formatter.h"

#include <sstream>

#include "../common_src/converter.h"
#include "../common_src/data.h"
#include "../common_src/text_splitter.h"

std::string Formatter::equipment_to_screen(Equipment&& e) {

    std::stringstream equipment;
    equipment << "money: $" << e.money;
    equipment << " | knife: " << (e.knife ? "equipped" : "not_equipped");

    equipment << " | primary: ";
    if (e.primary != NOT_EQUIPPED)
        equipment << e.primary + ", " << e.primary_ammo;
    else
        equipment << "not_equipped";

    equipment << " | secondary: ";
    if (e.secondary != NOT_EQUIPPED)
        equipment << e.secondary + ", " << e.secondary_ammo;
    else
        equipment << "not_equipped";

    return equipment.str();
}
