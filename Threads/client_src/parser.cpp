#include "parser.h"

#include "../common_src/constants.h"

ClientCommand Parser::parse_client_command(const std::string& msg) {
    ClientCommand cc;

    auto split = txt_splitter.split_text(msg, SPACE);

    cc.cmd = split[0];

    if (cc.cmd == CREAR || cc.cmd == UNIRSE) {
        cc.party_name = split[1];
    } else if (cc.cmd == JUGAR) {
        cc.column += std::stoi(split[1]);
        cc.row += std::stoi(split[2]);
    }

    return cc;
}
