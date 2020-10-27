#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "lane.hpp"

namespace fs = std::filesystem;

class FilesReader : public ILane {
public:
    FilesReader(const std::string& directory);

    std::vector<Lane> getLanes() const override { return lanes_; };

private:
    fs::path directoryPath_;
    std::vector<fs::path> files_;
    std::vector<Lane> lanes_;

    void checkDirectory() const;
    void makeFileList();
    void populateLanesFromFiles();

    std::vector<std::string> readFile(const fs::path& file);
    bool isValidPlayer(const std::string& line);
};
