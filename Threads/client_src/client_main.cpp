#include <iostream>

#include "../common_src/constants.h"

#include "client.h"

#define NUM_ARGS 3

int main(int argc, char* argv[]) {

    if (argc != NUM_ARGS) {
        std::cerr << "Please use: " << argv[0] << " <host> <port>" << std::endl;
        return ERROR;
    }

    std::string host(argv[1]), port(argv[2]);
    try {
        Client client(host, port);
        client.run();
    } catch (...) {
        return ERROR;
    }

    return SUCCESS;
}
