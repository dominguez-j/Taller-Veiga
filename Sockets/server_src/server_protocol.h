#ifndef __SERVER_PROTOCOL_H__
#define __SERVER_PROTOCOL_H__

#include <string>
#include <utility>

#include "../common_src/buy_request.h"
#include "../common_src/equipment.h"
#include "../common_src/socket.h"

class ServerProtocol {
private:
    const std::string servname;
    const std::string type_of_protocol;
    Socket peer;

    /*
     * Formatea y envia el mensaje a enviar al cliente en protocolo binario o de texto.
     */
    void serialize_binary(Equipment&& e);
    void serialize_text(Equipment&& e);

    /*
     * Deformatea y devuelve el mensaje que envia el cliente en protocolo binario o de texto.
     */
    BuyRequest deserialize_binary(bool& connected);
    BuyRequest deserialize_text(bool& connected);

    ServerProtocol(const ServerProtocol&) = delete;
    ServerProtocol& operator=(const ServerProtocol&) = delete;

public:
    ServerProtocol(const std::string& servname, const std::string& type_of_protocol, Socket&& peer):
            servname(servname), type_of_protocol(type_of_protocol), peer(std::move(peer)) {}

    void send_equipment(Equipment&& e);
    void send_protocol();
    BuyRequest receive_buy_request(bool& connected);
    std::string receive_username();

    ServerProtocol(ServerProtocol&&) = default;
    ServerProtocol& operator=(ServerProtocol&&) = default;

    ~ServerProtocol() = default;
};

#endif  // __SERVER_PROTOCOL_H__
