#include "lane.hpp"

void Lane::addPlayers(std::vector<std::string> lines) {
    for (auto& line : lines) {
        addPlayer(line);
    }
}
void Lane::addPlayer(std::string& line) {
    auto separatorPos = line.find(NAME_DELIMITER_SIGN);
    auto playerName = line.substr(0, separatorPos);
    auto playerGame = line.substr(separatorPos + 1);

    if (playerGame == "")
        return;

    players_.push_back({playerName, playerGame});
}
