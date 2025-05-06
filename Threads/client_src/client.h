#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <utility>

#include "client_protocol.h"
#include "parser.h"
#include "verificator.h"

class Client {
private:
    ClientProtocol protocol;
    Parser parser;
    Verificator verificator;

    void send_command(const std::string& msg);
    void receive_response(bool& connected);

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

public:
    Client(const std::string& host, const std::string& port): protocol(host, port) {}

    void run();

    Client(Client&&) = default;
    Client& operator=(Client&&) = default;

    ~Client() = default;
};

#endif  // CLIENT_H
