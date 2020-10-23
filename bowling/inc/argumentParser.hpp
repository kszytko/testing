#pragma once

#include <string>
#include <vector>

class ArgumentParser {
public:
    ArgumentParser(size_t size, char** arguments);

    std::string getAppName() const;
    std::string getInputDirectory() const;
    std::string getOutputFileName() const;
    bool isHelpNeeded() const;

private:
    size_t size_{};
    std::vector<std::string> arguments_{};

    void fillArgumentsVector(char** arguments);
    std::string getExistingArgument(size_t index) const;
    bool argumentExists(const std::string& option) const;
};
