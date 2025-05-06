#include <iostream>

#include "../common_src/constants.h"

#include "server.h"

#define NUM_ARGS 2

int main(int argc, char* argv[]) {

    if (argc != NUM_ARGS) {
        std::cerr << "Please use: " << argv[0] << " <port>" << std::endl;
        return ERROR;
    }

    std::string port(argv[1]);
    try {
        Server server(port);
        server.run();
    } catch (...) {
        return ERROR;
    }

    return SUCCESS;
}
