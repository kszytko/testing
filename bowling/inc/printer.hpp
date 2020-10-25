#pragma once

#include "printableData.hpp"

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

    void print(std::vector<LaneStruct>& lanes) const;

private:
    void printHeader(LaneStruct& lane) const;
    std::string parseStatus(const Status& status) const;
    void printPlayers(LaneStruct& lane) const;
    void printPlayer(Player& player) const;

private:
    std::unique_ptr<std::ostream> stream_;
    std::unique_ptr<std::fstream> file_;
};
