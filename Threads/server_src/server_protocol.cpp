#include "server_protocol.h"

#include <string>
#include <vector>

#include <netinet/in.h>

#include "../common_src/constants.h"

ClientCommand ServerProtocol::receive_command() {
    ClientCommand cc;
    cc.cmd = converter.bin_to_cmd(recv_uint8_t());

    if (cc.cmd == CREAR || cc.cmd == UNIRSE) {
        cc.party_name = recv_string(recv_uint16_t());
    } else if (cc.cmd == JUGAR) {
        uint8_t column_row = recv_uint8_t();
        cc.column = column_row >> 4;
        cc.row = column_row & 0x0F;
    }

    return cc;
}

void ServerProtocol::send_response(std::stringstream&& response) {
    std::string msg = response.str();
    send_uint16_t(msg.size());
    send_string(msg);
}

void ServerProtocol::kill() {
    skt.shutdown(2);
    skt.close();
}
