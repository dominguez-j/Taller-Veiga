#include "client_protocol.h"

#include <utility>
#include <vector>

#include <netinet/in.h>

#include "../common_src/constants.h"
#include "../common_src/converter.h"

#define MAX_MSG_SIZE 150

void ClientProtocol::send_command(const ClientCommand& cc) {
    uint8_t cmd = converter.cmd_to_bin(cc.cmd);
    skt.sendall(&cmd, sizeof(cmd));

    if (cc.cmd == CREAR || cc.cmd == UNIRSE) {
        uint16_t party_name_size = htons(cc.party_name.size());

        skt.sendall(&party_name_size, sizeof(party_name_size));
        skt.sendall(cc.party_name.c_str(), cc.party_name.size());
    } else if (cc.cmd == JUGAR) {
        uint8_t column_row = (cc.column << 4) | cc.row;

        skt.sendall(&column_row, sizeof(column_row));
    }
}

std::string ClientProtocol::receive_response(bool& connected) {
    uint16_t msg_size;
    skt.recvall(&msg_size, sizeof(msg_size));
    msg_size = ntohs(msg_size);

    std::string msg;
    std::vector<char> buffer(msg_size);

    while (msg.size() < msg_size) {
        int bytes_received = skt.recvsome(buffer.data(), buffer.size());
        if (bytes_received == 0) {
            connected = false;
            return EMPTY_MSG;
        }

        msg.append(buffer.data(), bytes_received);
    }
    return msg;
}
