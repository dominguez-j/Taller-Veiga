#include "server_protocol.h"

#include <string>
#include <vector>

#include <netinet/in.h>

#include "../common_src/constants.h"

ClientCommand ServerProtocol::receive_command() {
    ClientCommand cc;

    uint8_t cmd;
    peer.recvall(&cmd, sizeof(cmd));

    cc.cmd = converter.bin_to_cmd(cmd);

    if (cc.cmd == CREAR || cc.cmd == UNIRSE) {
        uint16_t party_name_size;
        peer.recvall(&party_name_size, sizeof(party_name_size));
        party_name_size = ntohs(party_name_size);

        std::vector<char> party_name(party_name_size);
        peer.recvall(party_name.data(), party_name.size());

        cc.party_name = std::string(party_name.data(), party_name.size());
    } else if (cc.cmd == JUGAR) {
        uint8_t column_row;
        peer.recvall(&column_row, sizeof(column_row));

        cc.column = column_row >> 4;
        cc.row = column_row & 0x0F;
    }

    return cc;
}

void ServerProtocol::send_response(std::stringstream response) {
    uint16_t msg_size = htons(response.str().size());

    peer.sendall(&msg_size, sizeof(msg_size));
    peer.sendall(response.str().c_str(), response.str().size());
}
