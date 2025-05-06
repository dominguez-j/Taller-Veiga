#include "server.h"

#include <utility>

#include "acceptor.h"
#include "lobby.h"

#define EXIT "q"

void Server::run() {

    Lobby lobby;
    Acceptor acceptor(port.c_str(), lobby);

    std::string input;
    while (input != EXIT) std::getline(std::cin, input);
}
