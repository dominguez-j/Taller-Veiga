#ifndef LOBBY_H
#define LOBBY_H

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "match.h"

class Lobby {
private:
    std::mutex mtx;
    std::map<std::string, std::shared_ptr<Match>> matches;

    Lobby(const Lobby&) = delete;
    Lobby& operator=(const Lobby&) = delete;

public:
    Lobby() = default;

    std::shared_ptr<Match> create_match(const std::string& party_name);
    std::shared_ptr<Match> join_match(const std::string& party_name);
    std::vector<std::string> show_matches();

    Lobby(Lobby&&) = default;
    Lobby& operator=(Lobby&&) = default;

    ~Lobby() { matches.clear(); }
};

#endif  // LOBBY_H
