#pragma once

#include <string>
#include <vector>

class Lane {
public:
    Lane(const std::string& name) : name_(name) {}

    size_t getPlayersNum() const { return players_.size(); }
    std::string getPlayer(size_t index) const {
        if (index < players_.size()) {
            return players_[index];
        }
        return "";
    }
    std::string getName() const { return name_; }

    void addPlayer(const std::string& player) { players_.push_back(player); }

public:
    std::string name_;
    std::vector<std::string> players_;
};
