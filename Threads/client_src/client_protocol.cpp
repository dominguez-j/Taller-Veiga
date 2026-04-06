#include "client_protocol.h"

#include <utility>
#include <vector>

#include <netinet/in.h>

#include "../common_src/constants.h"
#include "../common_src/converter.h"

#define MAX_MSG_SIZE 150

void ClientProtocol::send_command(const ClientCommand& cc) {
    send_uint8_t(converter.cmd_to_bin(cc.cmd));

    if (cc.cmd == CREAR || cc.cmd == UNIRSE) {
        send_uint16_t(cc.party_name.size());
        send_string(cc.party_name);
    } else if (cc.cmd == JUGAR) {
        send_uint8_t((cc.column << 4) | cc.row);
    }
}

std::string ClientProtocol::receive_response() {
    std::string msg = recv_string(recv_uint16_t());
    return msg.empty() ? EMPTY_MSG : msg;
}
