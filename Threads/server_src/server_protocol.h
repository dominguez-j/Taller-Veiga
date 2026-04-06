#ifndef SERVER_PROTOCOL_H
#define SERVER_PROTOCOL_H

#include <sstream>
#include <utility>

#include "../common_src/client_command.h"
#include "../common_src/converter.h"
#include "../common_src/protocol.h"
#include "../common_src/socket.h"

#include "board.h"

class ServerProtocol: public Protocol {
private:
    Converter converter;

    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

public:
    explicit ServerProtocol(Socket& peer): Protocol(std::move(peer)) {}

    ClientCommand receive_command();
    void send_response(std::stringstream&& response);
    void kill();

    ServerProtocol(ServerProtocol&&) = default;
    ServerProtocol& operator=(ServerProtocol&&) = default;

    ~ServerProtocol() = default;
};

#endif  // SERVER_PROTOCOL_H
