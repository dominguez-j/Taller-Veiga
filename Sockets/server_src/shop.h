#ifndef __SHOP_H__
#define __SHOP_H__

#include <string>

#include "../common_src/buy_request.h"

#include "player.h"

class Shop {
private:
    static void print_purchase_failed(const std::string& cmd);

public:
    static void try_purchase(BuyRequest&& buy_request, Player& player);
};

#endif  //__SHOP_H__
