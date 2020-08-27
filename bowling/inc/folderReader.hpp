#pragma once

#include <string>
#include <filesystem>
#include <vector>

#include "exceptions.hpp"
#include "fileReader.hpp"

namespace fs = std::filesystem;

class FolderReader {
public:
    FolderReader(const std::string& path) : path_(path) {
        checkDirectory();
        readDirectory();
        readFiles();
    }

    std::vector<fs::path> getFilePaths() { return files_; }
    std::vector<FileReader> * getFileReaders() { return &fileReaders_; }

private:
    void checkDirectory();
    void readDirectory();;
    void readFiles();

private:
    std::string path_;
    std::vector<fs::path> files_;
    std::vector<FileReader> fileReaders_;
};