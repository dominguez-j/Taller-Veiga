#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <string>
#include <utility>

#include <netinet/in.h>

#include "buffer.h"
#include "socket.h"

class Protocol {
protected:
    Socket skt;

    explicit Protocol(Socket&& skt): skt(std::move(skt)) {}

    void send_uint8_t(uint8_t value) { skt.sendall(&value, sizeof(value)); }

    void send_uint16_t(uint16_t value) {
        uint16_t net_value = htons(value);
        skt.sendall(&net_value, sizeof(net_value));
    }

    void send_string(const std::string& str) { skt.sendall(str.c_str(), str.size()); }

    uint8_t recv_uint8_t() {
        uint8_t value = 0;
        skt.recvall(&value, sizeof(value));
        return value;
    }

    uint16_t recv_uint16_t() {
        uint16_t value = 0;
        skt.recvall(&value, sizeof(value));
        return ntohs(value);
    }

    std::string recv_string(size_t size) {
        Buffer buffer(size);
        skt.recvall(buffer.data(), size);
        return std::string(buffer.data(), size);
    }

    Protocol(const Protocol&) = delete;
    Protocol& operator=(const Protocol&) = delete;

    Protocol(Protocol&&) = default;
    Protocol& operator=(Protocol&&) = default;

    ~Protocol() = default;
};

#endif  // __PROTOCOL_H__
