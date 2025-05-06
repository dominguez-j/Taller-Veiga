#include "client.h"

#include <iostream>

#include <netinet/in.h>

#define SIZE_ONLY_BOARD_MSG 128

void Client::send_command(const std::string& msg) {
    protocol.send_command(parser.parse_client_command(msg));
}

void Client::receive_response(bool& connected) {
    if (connected) {
        std::string response = protocol.receive_response(connected);
        std::cout << response;
        if (response.size() > SIZE_ONLY_BOARD_MSG)  // Si terminó la partida, el mensaje es mayor
            connected = false;
    }
}

void Client::run() {
    bool connected = true;
    std::string message;
    while (connected) {
        std::getline(std::cin, message);
        if (!verificator.verificate_operation(message)) {
            continue;
        } else {
            send_command(message);
            receive_response(connected);
        }
    }
}
