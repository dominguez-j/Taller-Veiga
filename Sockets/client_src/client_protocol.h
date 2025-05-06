#ifndef __CLIENT_PROTOCOL_H__
#define __CLIENT_PROTOCOL_H__

#include <string>

#include "../common_src/buy_request.h"
#include "../common_src/equipment.h"
#include "../common_src/socket.h"

class ClientProtocol {
private:
    Socket skt;
    std::string type_of_protocol;

    void send_username(const std::string& username);
    void receive_protocol();

    /*
     * Formatea y envia el mensaje a enviar al servidor en protocolo binario o de texto.
     */
    void serialize_binary(BuyRequest&& buy_request);
    void serialize_text(BuyRequest&& buy_request);

    /*
     * Deformatea y devuelve el mensaje que envia el servidor en protocolo binario o de texto.
     */
    Equipment deserialize_binary(bool& connected);
    Equipment deserialize_text(bool& connected);

    /*
        Recibe una parte del mensaje y devuelve el valor correspondiente.
    */
    int receive_value(const std::string& part_of_msg, std::string& value, const char delimiter);

    ClientProtocol(const ClientProtocol&) = delete;
    ClientProtocol& operator=(const ClientProtocol&) = delete;

public:
    ClientProtocol(const std::string& hostname, const std::string& servname,
                   const std::string& username):
            skt(hostname.c_str(), servname.c_str()) {
        send_username(username);
        receive_protocol();
    }

    void send_buy_request(BuyRequest&& buy_request);
    Equipment receive_equipment(bool& connected);

    ClientProtocol(ClientProtocol&&) = default;
    ClientProtocol& operator=(ClientProtocol&&) = default;

    ~ClientProtocol() = default;
};
#endif  // __CLIENT_PROTOCOL_H__
