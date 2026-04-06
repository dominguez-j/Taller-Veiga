#include "client_handler.h"

#include <utility>

#include "../common_src/constants.h"

void ClientHandler::send_game_state(const std::string& message) {
    std::stringstream state = ss_f.format_table(match->get_table(), message);
    protocol.send_response(std::move(state));
}

void ClientHandler::handle_move(const ClientCommand& cmd) {
    match->make_move(cmd.row, cmd.column, player_value);
}

bool ClientHandler::handle_game_state(std::string& message) {
    char winner = match->has_winner();

    if (winner != IN_PROGRESS) {
        if (winner == player_value) {
            message = WIN_MSG;
        } else if (winner == DRAW) {
            message = DRAW_MSG;
        } else {
            message = LOSE_MSG;
        }
        return true;
    }

    return false;
}

void ClientHandler::play() {
    while (is_alive) {
        match->wait_turn(player_value);
        std::string message = EMPTY_MSG;
        bool finished = handle_game_state(message);
        send_game_state(message);

        if (finished) {
            match->finish_turn();
            break;
        }

        ClientCommand cmd = protocol.receive_command();
        if (cmd.cmd == JUGAR)
            handle_move(cmd);
        else
            break;
        match->finish_turn();
    }
    stop();
}

void ClientHandler::handle_create(const ClientCommand& cmd) {
    match = lobby.create_match(cmd.party_name);
    if (!match)
        return;
    player_value = CIRCLE;
    play();
}

void ClientHandler::handle_join(const ClientCommand& cmd) {
    match = lobby.join_match(cmd.party_name);
    if (!match)
        return;
    player_value = CROSS;
    play();
}

void ClientHandler::handle_list(const ClientCommand& cmd) {
    protocol.send_response(ss_f.format_party_list(lobby.show_matches()));
}

void ClientHandler::stop() { is_alive = false; }

void ClientHandler::run() {
    while (is_alive) {
        ClientCommand cmd = protocol.receive_command();
        if (handlers.count(cmd.cmd)) {
            (this->*handlers[cmd.cmd])(cmd);
        }
    }
}

const bool ClientHandler::is_dead() const { return !is_alive; }
