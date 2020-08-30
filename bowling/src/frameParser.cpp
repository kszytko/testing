#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>

#include "frameParser.hpp"
#include "tokenizer.hpp"

const char FrameParser::StrikeSign = 'X';
const char FrameParser::MissSign = '-';
const char FrameParser::SpareSign = '/';

size_t FrameParser::parseToken(const char token, size_t& lastParsedToken) {
    if (token == FrameParser::StrikeSign) {
        lastParsedToken = 10;
        return lastParsedToken;
    } else if (token == FrameParser::SpareSign) {
        lastParsedToken = 10 - lastParsedToken;
        return lastParsedToken;
    } else if (token == FrameParser::MissSign) {
        lastParsedToken = 0;
        return lastParsedToken;
    } else {
        lastParsedToken = token - '0';
        return lastParsedToken;
    }
}

parsedFrame FrameParser::parse(const std::string& line) {
    std::vector<size_t> parsed{};
    size_t currentLinePosition{};
    size_t lastParsedToken{};

    auto name = Tokenizer::readName(line, currentLinePosition);
    auto sequence = Tokenizer::readSequence(line, currentLinePosition);

    std::transform(sequence.cbegin(), sequence.cend(), back_inserter(parsed),
                   std::bind(FrameParser::parseToken, std::placeholders::_1, lastParsedToken));

    return std::pair(name, parsed);
}
