#include "printer.hpp"
#include <sstream>

void Printer::print(const std::vector<LaneStruct>& lanes) {
    for (auto& lane : lanes) {
        printHeader(lane);
        printPlayers(lane);
    }
}

void Printer::printHeader(const LaneStruct& lane) const {
    std::stringstream s;
    s << "### " << lane.name_ << ": " << parseStatus(lane.status_) << " ###\n";
    printData(s.str());
}

void Printer::printData(std::string text) const {
    stream_->print(text);
}

void Printer::printData(size_t value) const {
    stream_->print(value);
}

std::string Printer::parseStatus(const Status status) const {
    switch (status) {
    case Status::NO_GAME:
        return "no game";

    case Status::IN_PROGRESS:
        return "game in progress";

    case Status::FINISHED:
        return "game finished";

    default:
        return "";
    }
}

void Printer::printPlayers(const LaneStruct& lane) const {
    for (auto& player : lane.players_) {
        printPlayer(player);
        printData("\n");
    }
}

void Printer::printPlayer(const Player& player) const {
    if (!player.name_.empty()) {
        printData(player.name_ + " ");
    }
    printData(player.score_);
}
