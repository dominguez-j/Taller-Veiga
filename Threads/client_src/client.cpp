#include "client.h"

#include <iostream>

#include <netinet/in.h>

#include "../common_src/printer.h"

#define SIZE_ONLY_BOARD_MSG 128

void Client::send_command(const std::string& msg) {
    protocol.send_command(parser.parse_client_command(msg));
}

void Client::receive_response() {
    std::string response = protocol.receive_response();
    Printer::print(response);
    if (response.size() > SIZE_ONLY_BOARD_MSG)  // Si terminó la partida, el mensaje es mayor
        has_finished = true;
}

void Client::run() {
    std::string message;
    while (!has_finished) {
        std::getline(std::cin, message);
        if (!verificator.verificate_operation(message)) {
            continue;
        } else {
            send_command(message);
            receive_response();
        }
    }
}
