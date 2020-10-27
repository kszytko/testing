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
    Lane(const std::string& name) : name_(name), status_(Status::NO_GAME){};
    void addPlayer(const std::string& line);

    std::string name_;
    Status status_;
    std::vector<Player> players_;
};

class ILane {
public:
    virtual ~ILane(){};
    virtual std::vector<Lane> getLanes() const = 0;
};
