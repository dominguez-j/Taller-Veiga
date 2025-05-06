#include "parser.h"

#include "converter.h"
#include "data.h"
#include "text_splitter.h"

BuyRequest Parser::parse_buy_request_from_server(const std::string& message) {
    BuyRequest buy_request;

    /*Se pueden recibir dos posibles comandos:
    1. buy.weapon:<weapon>
    2. buy.ammo.<weapon-type>:<count>
    */
    auto colon_split = TextSplitter::split_text(message, COLON);  // Separo por :

    // El split en este caso devuelve un vector de 2 strings
    // Significa que es "buy.weapon", "<weapon>" o "buy.ammo.<weapon-type>", "<count>"
    if (colon_split[0] == Converter::cmd_translation(BUY)) {  // Si es "buy.weapon"
        buy_request.command = BUY;
        buy_request.weapon_name = colon_split[1];
    } else {  // Si no, es "buy.ammo"
        // El segundo, hace split de "buy.ammo.<weapon-type>" separando por "."
        // Dando así un vector de 3 strings. "buy", "ammo", "<weapon-type>"
        auto dot_split = TextSplitter::split_text(colon_split[0], DOT);
        buy_request.command = AMMO;
        buy_request.ammo_count = stoi(colon_split[1]);
        buy_request.weapon_type = dot_split[2];
    }
    return buy_request;
}

Equipment Parser::parse_equipment_from_client(const std::string& message) {
    Equipment e;

    /*
    Voy a tener 4 splits por los saltos de linea:
    1. equipment.money:<money>
    2. equipment.knife:<knife>
    3. equipment.primary:<primary>,<primary_ammo>
    4. equipment.secondary:<secondary>,<secondary_ammo>
    */
    auto endl_split = TextSplitter::split_text(message, END_OF_LINE);

    // Hago el split de cada uno por el : para separar el comando del valor
    auto money_split = TextSplitter::split_text(endl_split[0], COLON);
    auto knife_split = TextSplitter::split_text(endl_split[1], COLON);
    auto primary_split = TextSplitter::split_text(endl_split[2], COLON);
    auto secondary_split = TextSplitter::split_text(endl_split[3], COLON);

    e.money = std::stoi(money_split[1]);
    e.knife = (knife_split[1] == "true" ? true : false);

    // Hago el split por la , para separar el arma de la cantidad
    auto primary_split_2 = TextSplitter::split_text(primary_split[1], COMMA);
    auto secondary_split_2 = TextSplitter::split_text(secondary_split[1], COMMA);
    e.primary = primary_split_2[0];
    e.primary_ammo = std::stoi(primary_split_2[1]);
    e.secondary = secondary_split_2[0];
    e.secondary_ammo = std::stoi(secondary_split_2[1]);

    return e;
}

BuyRequest Parser::parse_buy_request_from_client(const std::string& message) {
    auto split_message = TextSplitter::split_text(message, SPACE);
    BuyRequest buy_request;

    buy_request.command = split_message[0];
    if (split_message[0] == BUY) {
        buy_request.weapon_name = split_message[1];
    } else {
        buy_request.weapon_type = Converter::weapon_to_type(split_message[1]);
        buy_request.ammo_count = std::stoi(split_message[2]);
    }

    return buy_request;
}
