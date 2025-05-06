#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <list>
#include <string>

#include "../common_src/socket.h"

#include "client_handler.h"
#include "thread.h"

class Acceptor: public Thread {
private:
    Socket acceptor;
    std::list<ClientHandler*> clients;
    bool is_alive = true;
    Lobby& lobby;

    void reap();
    void clear();

    Acceptor(const Acceptor&) = delete;
    Acceptor& operator=(const Acceptor&) = delete;

public:
    Acceptor(const std::string& port, Lobby& lobby): acceptor(port.c_str()), lobby(lobby) {
        start();
    }

    void run() override;

    Acceptor(Acceptor&&) = default;
    Acceptor& operator=(Acceptor&&) = default;

    ~Acceptor() {
        acceptor.shutdown(2);
        acceptor.close();
        clear();
        join();
    }
};

#endif  // ACCEPTOR_H
