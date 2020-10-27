#pragma once

#include "lane.hpp"
#include "scoreCounter.hpp"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class Printer {
public:
    explicit Printer(const std::ostream& outStream);
    explicit Printer(const std::string& filename = "");
    ~Printer();

    void print(const ILane& score) const;

private:
    void printLanes(const std::vector<Lane>& lanes) const;
    void printHeader(const Lane& lane) const;
    std::string parseStatus(const Status& status) const;
    void printPlayers(const Lane& lane) const;
    void printPlayer(const Player& player) const;

    std::unique_ptr<std::ostream> stream_;
    std::unique_ptr<std::fstream> file_;
};
