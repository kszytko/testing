#pragma once

#include "printableData.hpp"

#include <string>
#include <vector>
#include <memory>
#include <sstream>

class Printer{
public:
    void print(std::vector<LaneStruct> lanes, std::ostream& outputStream);

private:
    void printHeader(LaneStruct & lane);
    std::string parseStatus(const Status & status);
    void printPlayers(LaneStruct & lane);
    void printPlayer(Player & player);

private:
    std::stringstream stream_;
};
