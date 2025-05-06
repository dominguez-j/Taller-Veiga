#ifndef SERVER_H
#define SERVER_H

#include <string>

#include "server_protocol.h"

class Server {
private:
    std::string port;

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

public:
    explicit Server(const std::string& port): port(port) {}

    void run();

    Server(Server&&) = default;
    Server& operator=(Server&&) = default;

    ~Server() = default;
};

#endif  // SERVER_H
