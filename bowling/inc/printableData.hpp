#pragma once

#include <string>
#include <vector>

enum class Status { 
    NO_GAME, 
    IN_PROGRESS, 
    FINISHED 
};

struct Player {
    Player(std::string name, size_t score) : name_(name), score_(score){};

    std::string name_;
    size_t score_;
};

struct LaneStruct {
    LaneStruct(){};
    LaneStruct(std::string name, Status status) : name_(name), status_(status){};

    std::string name_;
    Status status_;
    std::vector<Player> players_;
};
