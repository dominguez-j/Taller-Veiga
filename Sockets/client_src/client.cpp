#include "client.h"

#include <iostream>
#include <utility>

#include <netinet/in.h>

#include "../common_src/data.h"
#include "../common_src/formatter.h"
#include "../common_src/parser.h"
#include "../common_src/printer.h"

#include "verificator.h"

#define EXIT_CMD "exit"

void Client::send_buy_request(BuyRequest&& buy_request) {
    protocol.send_buy_request(std::move(buy_request));
}

void Client::receive_equipment() {
    Printer::print(Formatter::equipment_to_screen(protocol.receive_equipment()));
}

void Client::run() {
    bool connected = true;
    receive_equipment();
    std::string message;
    while (connected) {
        std::getline(std::cin, message);
        if (message == EXIT_CMD) {
            connected = false;
        } else if (!Verificator::verificate_operation(message)) {
            continue;
        } else {
            send_buy_request(Parser::parse_buy_request_from_client(message));
            receive_equipment();
        }
    }
}
