#pragma once

#include "printableData.hpp"
#include "printerStream.hpp"

#include <string>
#include <vector>

class Printer {
public:
    Printer(PrinterStream* stream) : stream_(stream){};
    void print(const std::vector<LaneStruct>& lanes);

private:
    void printHeader(const LaneStruct& lane) const;
    void printData(std::string text) const;
    void printData(size_t value) const;
    std::string parseStatus(const Status status) const;
    void printPlayers(const LaneStruct& lane) const;
    void printPlayer(const Player& player) const;

private:
    PrinterStream* stream_;
};
