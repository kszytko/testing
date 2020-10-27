#pragma once

#include <string>
#include <vector>

constexpr char NAME_DELIMITER_SIGN = ':';

enum class Status { NO_GAME, IN_PROGRESS, FINISHED };

struct Player {
    std::string name_;
    std::string game_;
    size_t score_;
};

class Lane {
public:
    void addPlayer(std::string& line);
    void addPlayers(std::vector<std::string> lines);

    std::string name_;
    Status status_;
    std::vector<Player> players_;
};
