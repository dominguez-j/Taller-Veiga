#ifndef CLIENT_PROTOCOL_H
#define CLIENT_PROTOCOL_H

#include <string>

#include "../common_src/client_command.h"
#include "../common_src/converter.h"
#include "../common_src/protocol.h"
#include "../common_src/socket.h"

class ClientProtocol: public Protocol {
private:
    Converter converter;

    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

public:
    ClientProtocol(const std::string& host, const std::string& port):
            Protocol(Socket(host.c_str(), port.c_str())) {}

    void send_command(const ClientCommand& cc);
    std::string receive_response();

    ClientProtocol(ClientProtocol&&) = default;
    ClientProtocol& operator=(ClientProtocol&&) = default;

    ~ClientProtocol() = default;
};

#endif  // CLIENT_PROTOCOL_H
