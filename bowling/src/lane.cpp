#include "lane.hpp"

void Lane::addPlayer(const std::string& line) {
    auto separatorPos = line.find(NAME_DELIMITER_SIGN);
    auto playerName = line.substr(0, separatorPos);
    auto playerGame = line.substr(separatorPos + 1);

    players_.push_back({playerName, playerGame, 0});
}
