#include "lobby.h"

#include <algorithm>

#include <bits/algorithmfwd.h>

std::shared_ptr<Match> Lobby::create_match(const std::string& party_name) {
    std::lock_guard<std::mutex> lock(mtx);
    auto match = std::make_shared<Match>(party_name);
    matches[party_name] = match;
    return match;
}

std::shared_ptr<Match> Lobby::join_match(const std::string& party_name) {
    std::lock_guard<std::mutex> lock(mtx);
    auto match = matches.find(party_name);

    if (match != matches.end())
        return match->second;

    return nullptr;
}

std::vector<std::string> Lobby::show_matches() {
    std::lock_guard<std::mutex> lock(mtx);
    std::vector<std::string> party_names;

    std::transform(matches.begin(), matches.end(), std::back_inserter(party_names),
                   [](const auto& match) { return match.first; });

    return party_names;
}
