#ifndef __SERVER_H__
#define __SERVER_H__

#include <string>

#include "player.h"
#include "server_protocol.h"

class Server {
private:
    Socket skt;
    ServerProtocol protocol;
    Player player;

    void welcome_message(const std::string& username) const;
    void send_protocol();
    void send_player_equipment();
    void create_player();
    BuyRequest receive_buy_request(bool& connected);

    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;

public:
    Server(const std::string& servname, const std::string& type_of_protocol):
            skt(servname.c_str()),
            protocol(servname, type_of_protocol, this->skt.accept()),
            player("") {}

    void run();

    Server(Server&&) = default;
    Server& operator=(Server&&) = default;

    ~Server() = default;
};

#endif  // __SERVER_H__
