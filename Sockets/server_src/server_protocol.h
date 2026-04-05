#ifndef __SERVER_PROTOCOL_H__
#define __SERVER_PROTOCOL_H__

#include <string>
#include <utility>

#include "../common_src/buy_request.h"
#include "../common_src/equipment.h"
#include "../common_src/protocol.h"

class ServerProtocol: public Protocol {
private:
    void serialize_binary(Equipment&& e);
    void serialize_text(Equipment&& e);

    BuyRequest deserialize_binary();
    BuyRequest deserialize_text();

    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

public:
    ServerProtocol(const std::string& servname, const std::string& type_of_protocol, Socket&& peer):
            Protocol(std::move(peer), type_of_protocol) {}

    void send_equipment(Equipment&& e);
    void send_protocol();
    BuyRequest receive_buy_request();
    std::string receive_username();

    ServerProtocol(ServerProtocol&&) = default;
    ServerProtocol& operator=(ServerProtocol&&) = default;

    ~ServerProtocol() = default;
};

#endif  // __SERVER_PROTOCOL_H__
