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

struct Lane {
    void addPlayer(const std::string& line);

    std::string name_;
    Status status_;
    std::vector<Player> players_;
};
