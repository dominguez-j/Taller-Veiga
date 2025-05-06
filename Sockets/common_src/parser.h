#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>

#include "buy_request.h"
#include "equipment.h"

class Parser {
public:
    static BuyRequest parse_buy_request_from_server(const std::string& message);

    static Equipment parse_equipment_from_client(const std::string& message);
    static BuyRequest parse_buy_request_from_client(const std::string& message);
};

#endif  // __PARSER_H__
