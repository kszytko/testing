#include <algorithm>
#include <functional>

#include "frameParser.hpp"
#include "tokenizer.hpp"

const char FrameParser::StrikeSign = 'X';
const char FrameParser::MissSign = '-';
const char FrameParser::SpareSign = '/';

void FrameParser::parseToken(const char token, size_t& lastRollValue) {
    switch (token) {
    case FrameParser::StrikeSign:
        lastRollValue = 10;
        break;
    case FrameParser::SpareSign:
        lastRollValue = 10 - lastRollValue;
        break;
    case FrameParser::MissSign:
        lastRollValue = 0;
        break;
    default:
        lastRollValue = static_cast<size_t>(token - '0');
        break;
    }
}

parsedFrame FrameParser::parse(const std::string& line) {
    std::vector<size_t> parsed{};
    size_t lastRollValue{};

    auto sequence = Tokenizer::readSequence(line);

    std::for_each(sequence.cbegin(), sequence.cend(), [&lastRollValue, &parsed](const auto& el) {
        FrameParser::parseToken(el, lastRollValue);
        parsed.push_back(lastRollValue);
    });

    return parsed;
}

bool FrameParser::isSequenceComplete(const std::string& line) {
    const std::string endOfSequenceDelimiter = "||";

    size_t endOfSequenceDelimiterPosition = line.find(endOfSequenceDelimiter);

    if (endOfSequenceDelimiterPosition == std::string::npos) {
        return false;
    } else {
        auto lastRegularToken = *(std::prev((line.cbegin() + endOfSequenceDelimiterPosition)));
        size_t numberOfTokensToLookFor;
        if (lastRegularToken == FrameParser::StrikeSign) {
            numberOfTokensToLookFor = 2;
            return areProperTokensAtTheEnd(line, endOfSequenceDelimiterPosition, numberOfTokensToLookFor);
        } else if (lastRegularToken == FrameParser::SpareSign) {
            numberOfTokensToLookFor = 1;
            return areProperTokensAtTheEnd(line, endOfSequenceDelimiterPosition, numberOfTokensToLookFor);
        } else {
            return true;
        }
    }
}

bool FrameParser::areProperTokensAtTheEnd(const std::string& line, size_t position, size_t numberOfTokensToLookFor) {
    std::string tokensAfterEndOfSequenceDelimiter = line.substr(position + 2, numberOfTokensToLookFor);

    return tokensAfterEndOfSequenceDelimiter.length() == numberOfTokensToLookFor &&
           std::all_of(tokensAfterEndOfSequenceDelimiter.cbegin(), tokensAfterEndOfSequenceDelimiter.cend(),
                       [](const auto& el) {
                           return std::isdigit(el) || el == FrameParser::StrikeSign || el == FrameParser::MissSign;
                       });
}
