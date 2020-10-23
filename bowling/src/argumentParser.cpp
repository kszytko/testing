#include "argumentParser.hpp"

#include <algorithm>

ArgumentParser::ArgumentParser(size_t size, char** arguments) {
    size_ = size;
    fillArgumentsVector(arguments);
}

void ArgumentParser::fillArgumentsVector(char** arguments) {
    arguments_.reserve(size_);
    for (size_t i = 0; i < size_; ++i) {
        arguments_.push_back(arguments[i]);
    }
}

std::string ArgumentParser::getAppName() const {
    return getExistingArgument(0);
}

std::string ArgumentParser::getInputDirectory() const {
    return getExistingArgument(1);
}

std::string ArgumentParser::getOutputFileName() const {
    return getExistingArgument(2);
}

bool ArgumentParser::isHelpNeeded() const {
    return size_ == 1 || size_ > 3 || argumentExists("-h") || argumentExists("--help");
}

std::string ArgumentParser::getExistingArgument(size_t index) const {
    if (index < size_) {
        return arguments_[index];
    }
    return "";
}

bool ArgumentParser::argumentExists(const std::string& option) const {
    return std::find(begin(arguments_), end(arguments_), option) != end(arguments_);
}
