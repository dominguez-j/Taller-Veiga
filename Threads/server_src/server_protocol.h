#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <sstream>
#include <utility>

#include "../common_src/client_command.h"
#include "../common_src/converter.h"
#include "../common_src/socket.h"

#include "board.h"

class ServerProtocol {
private:
    Socket peer;
    Converter converter;

    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

public:
    explicit ServerProtocol(Socket& peer): peer(std::move(peer)) {}

    ClientCommand receive_command();
    void send_response(std::stringstream response);
    void kill();

    ServerProtocol(ServerProtocol&&) = default;
    ServerProtocol& operator=(ServerProtocol&&) = default;

    ~ServerProtocol() {
        peer.shutdown(2);
        peer.close();
    }
};

#endif  // SERVER_PROTOCOL_H
