#include "consoleStream.hpp"

void ConsoleStream::print(const std::string& stringToPrint) {
    stream_ << stringToPrint;
}

void ConsoleStream::print(size_t valueToPrint) {
    stream_ << valueToPrint;
}

std::string ConsoleStream::str() const {
    return stream_.str();
}
