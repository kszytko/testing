#include <algorithm>

#include "tokenizer.hpp"

const char Tokenizer::FrameDelimiterSign = '|';

std::string Tokenizer::readSequence(const std::string& line) {
    std::string result{line};
    result.erase(std::remove(result.begin(), result.end(), FrameDelimiterSign), result.end());
    return result;
}

