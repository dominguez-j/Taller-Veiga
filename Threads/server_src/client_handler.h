#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <memory>
#include <string>

#include "../common_src/client_command.h"
#include "../common_src/socket.h"

#include "lobby.h"
#include "match.h"
#include "messages.h"
#include "server_protocol.h"
#include "ss_formatter.h"
#include "thread.h"

class ClientHandler: public Thread {
private:
    ServerProtocol protocol;
    Lobby& lobby;
    std::shared_ptr<Match> match;
    bool is_alive = true;
    char player_value = EMPTY;
    SSFormatter ss_f;

    void send_game_state(const std::string& message);
    void play();
    bool handle_game_state(std::string& message);
    void handle_move(const ClientCommand& cmd);
    void handle_list();
    void handle_join(const ClientCommand& cmd);
    void handle_create(const ClientCommand& cmd);
    void handle_command(const ClientCommand& cmd);

    ClientHandler(const ClientHandler&) = delete;
    ClientHandler& operator=(const ClientHandler&) = delete;

public:
    ClientHandler(Socket&& skt, Lobby& lobby): protocol(skt), lobby(lobby), match() {}

    void run() override;
    const bool is_dead() const;
    void kill();

    ClientHandler(ClientHandler&&) = default;
    ClientHandler& operator=(ClientHandler&&) = default;

    ~ClientHandler() = default;
};

#endif  // CLIENT_HANDLER_H
