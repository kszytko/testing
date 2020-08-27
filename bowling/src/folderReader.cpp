#include "folderReader.hpp"
#include "fileReader.hpp"

void FolderReader::checkDirectory() {
    if (!fs::exists(path_))
        throw DirectoryNotExists();

    if (!fs::is_directory(path_))
        throw PathIsNotDirectory();
}

void FolderReader::readDirectory() {
    for (const auto& entry : fs::directory_iterator(path_)) {
        auto filename = entry.path().filename();
        if (fs::is_regular_file(entry.status())) {
            files_.push_back(entry.path());
        }
    }
    files_.shrink_to_fit();
    std::sort(files_.begin(), files_.end());
}

void FolderReader::readFiles() {
    for(auto & file : files_){
        fileReaders_.emplace_back(file);
    }
}
