#include "tokenizer.hpp"

const char Tokenizer::FrameDelimiterSign = '|';
const char Tokenizer::NameDelimiterSign = ':';

std::string Tokenizer::readSequence(const std::string& line, size_t& position) {
    std::string result = {std::next(line.begin() + position), line.end()};

    result.erase(std::remove(result.begin(), result.end(), FrameDelimiterSign), result.end());

    return result;
}

std::string Tokenizer::readName(const std::string& line, size_t& position) {
    size_t next = line.find(NameDelimiterSign);
    if (next != std::string::npos) {
        position = next;
        return line.substr(0, next);
    } else {
        return "";
    }
}
