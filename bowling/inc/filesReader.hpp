#pragma once

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "lane.hpp"
#include "reader.hpp"

namespace fs = std::filesystem;

class FilesReader : public Reader {
public:
    FilesReader(const std::string& directory);

    size_t getLanesNum() const { return lanes_.size(); }
    Lane* getLane(size_t index);
    std::vector<Lane> getLanes() const override { return lanes_; };

private:
    fs::path directoryPath_;
    std::vector<fs::path> files_;
    std::vector<Lane> lanes_;

    void checkDirectory() const;
    void makeFileList();
    void readFiles();
    std::vector<std::string> readLines(const fs::path& file);
    bool isLineValid(std::string line);
};
