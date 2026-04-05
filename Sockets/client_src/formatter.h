#ifndef __FORMATTER_H__
#define __FORMATTER_H__

#include <string>

#include "../common_src/buy_request.h"
#include "../common_src/equipment.h"

class Formatter {
public:
    static std::string equipment_to_screen(Equipment&& e);
    static std::string welcome_message_to_screen(const std::string& username);
};

#endif  // __FORMATTER_H__
