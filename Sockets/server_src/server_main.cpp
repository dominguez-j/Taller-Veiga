#include <iostream>

#include "../common_src/data.h"

#include "server.h"

#define NUM_ARGS 3

int main(int argc, char* argv[]) {

    if (argc != NUM_ARGS) {
        std::cerr << "Please use: " << argv[0] << " <port> <type_of_protocol>" << std::endl;
        return ERROR;
    }

    std::string port(argv[1]), protocol(argv[2]);
    Server server(port, protocol);
    server.run();

    return SUCCESS;
}
