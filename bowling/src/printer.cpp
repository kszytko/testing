#include "printer.hpp"

#include <stdexcept>

Printer::Printer(const std::ostream& outStream) {
    stream_ = std::make_unique<std::ostream>(outStream.rdbuf());
}

Printer::Printer(const std::string& filename) {
    if (filename.empty()) {
        stream_ = std::make_unique<std::ostream>(std::cout.rdbuf());
    } else {
        file_ = std::make_unique<std::fstream>(filename, std::fstream::out | std::fstream::app);
        if (!file_->is_open()) {
            throw std::runtime_error("Open file not possible.");
        }
        stream_ = std::make_unique<std::ostream>(file_->rdbuf());
    }
}

Printer::~Printer() {
    if (file_) {
        file_->close();
    }
}

void Printer::print(ScoreCounter& score) const {
    printLanes(score.getLanes());
}

void Printer::printLanes(const std::vector<Lane>& lanes) const {
    for (auto& lane : lanes) {
        printHeader(lane);
        printPlayers(lane);
    }
}

void Printer::printHeader(const Lane& lane) const {
    *stream_ << "### " << lane.name_ << ": " << parseStatus(lane.status_) << " ###\n";
}

std::string Printer::parseStatus(const Status& status) const {
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

void Printer::printPlayers(const Lane& lane) const {
    for (auto& player : lane.players_) {
        printPlayer(player);
        *stream_ << "\n";
    }
}

void Printer::printPlayer(const Player& player) const {
    if (!player.name_.empty()) {
        *stream_ << player.name_ << " ";
    }
    *stream_ << player.score_;
}
