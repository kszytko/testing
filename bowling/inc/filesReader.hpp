#pragma once

#include <filesystem>
#include <memory>
#include <string>

#include "lane.hpp"

namespace fs = std::filesystem;

class FilesReader {
public:
    FilesReader(const std::string& directory);

    size_t getLanesNum() const { return lanes_.size(); }
    std::shared_ptr<Lane> getLane(size_t index) const;
    std::vector<std::shared_ptr<Lane>> getLanes() const {return lanes_;};

private:
    fs::path directoryPath_;
    std::vector<std::shared_ptr<Lane>> lanes_;

    void checkDirectory() const;
    std::vector<fs::path> makeFileList();
    void readFiles(const std::vector<fs::path>& files);
    void readPlayers(const fs::path& file, Lane& lane);
};
