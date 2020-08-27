#include "lane.hpp"

void Lane::addPlayers(std::vector<std::string> lines) {
    for(auto & line :  lines) {
        addPlayer(line);
    }
}
void Lane::addPlayer(std::string& line) {
    auto playerName = readPlayerName(line);
    auto playerGame = readPlayerGame(line);

    if(playerGame == "")
        return;

    players_.emplace_back(playerName, playerGame);
}

std::string Lane::readPlayerName(std::string& line) {
    return line.substr(0, getSeparatorPos(line));
}
std::string Lane::readPlayerGame(std::string& line) {
    return line.substr(getSeparatorPos(line) + 1);
}
unsigned int Lane::getSeparatorPos(std::string& line) {
    return line.find(':');
}
