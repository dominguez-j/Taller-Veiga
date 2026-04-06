#ifndef SERVER_H
#define SERVER_H

#include <string>

#include "server_protocol.h"

class Server {
private:
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

public:
    explicit Server(const std::string& port) { run(port); }

    void run(const std::string& port);

    Server(Server&&) = default;
    Server& operator=(Server&&) = default;

    ~Server() = default;
};

#endif  // SERVER_H
