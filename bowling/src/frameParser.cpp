#include <algorithm>
#include <functional>

#include "frameParser.hpp"
#include "tokenizer.hpp"

const char FrameParser::StrikeSign = 'X';
const char FrameParser::MissSign = '-';
const char FrameParser::SpareSign = '/';

size_t FrameParser::parseToken(const char token, size_t& lastParsedToken) {
    switch (token) {
    case FrameParser::StrikeSign:
        lastParsedToken = 10;
        break;
    case FrameParser::SpareSign:
        lastParsedToken = 10 - lastParsedToken;
        break;
    case FrameParser::MissSign:
        lastParsedToken = 0;
        break;
    default:
        lastParsedToken = token - '0';
        break;
    }
    return lastParsedToken;
}

parsedFrame FrameParser::parse(const std::string& line) {
    std::vector<size_t> parsed{};
    size_t lastParsedToken{};

    auto name = Tokenizer::readName(line);
    auto sequence = Tokenizer::readSequence(line);

    std::transform(sequence.cbegin(), sequence.cend(), back_inserter(parsed),
                   std::bind(FrameParser::parseToken, std::placeholders::_1, lastParsedToken));

    return std::pair(name, parsed);
}
