#include <iostream>

#include "../common_src/data.h"

#include "client.h"

#define NUM_ARGS 4

int main(int argc, char* argv[]) {

    if (argc != NUM_ARGS) {
        std::cerr << "Please use: " << argv[0] << " <hostname> <servname> <username>" << std::endl;
        return ERROR;
    }

    std::string hostname(argv[1]), servname(argv[2]), username(argv[3]);
    Client client(username, hostname, servname);
    client.run();

    return SUCCESS;
}
