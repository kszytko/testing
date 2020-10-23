#include "fileStream.hpp"

#include <stdexcept>

FileStream::FileStream(const std::string& filePath) {
    if (filePath.empty())
        throw std::invalid_argument("Invalid filename");

    file_ = new std::ofstream;
    file_->open(filePath);
}

FileStream::~FileStream() {
    file_->close();
    delete file_;
}

void FileStream::print(const std::string& stringToPrint) {
    *file_ << stringToPrint;
};

void FileStream::print(size_t valueToPrint) {
    *file_ << valueToPrint;
}
