#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <string>
#include <utility>

#include "../common_src/buy_request.h"

#include "client_protocol.h"

class Client {
private:
    const std::string username;
    ClientProtocol protocol;

    void send_buy_request(BuyRequest&& buy_request);
    void receive_equipment(bool& connected);

    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;

public:
    Client(const std::string& username, const std::string& hostname, const std::string& servname):
            username(username), protocol(hostname, servname, username) {}

    void run();

    Client(Client&&) = default;
    Client& operator=(Client&&) = default;

    ~Client() = default;
};

#endif  // __CLIENT_H__
