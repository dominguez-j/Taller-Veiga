#ifndef CLIENT_COMMAND_H
#define CLIENT_COMMAND_H

#include <cstdint>
#include <string>

struct ClientCommand {
    std::string cmd = "";
    std::string party_name = "";
    uint8_t column = -1;
    uint8_t row = -1;

    ClientCommand(const std::string& cmd, const std::string& party_name):
            cmd(cmd), party_name(party_name) {}

    ClientCommand(const std::string& cmd, uint8_t column, uint8_t row):
            cmd(cmd), column(column), row(row) {}

    explicit ClientCommand(const std::string& cmd): cmd(cmd) {}

    ClientCommand() {}
};

#endif  // CLIENT_COMMAND_H
