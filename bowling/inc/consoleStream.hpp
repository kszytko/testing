#pragma once

#include <sstream>
#include <string>

#include "printerStream.hpp"

class ConsoleStream : public PrinterStream {
public:
    void print(const std::string& stringToPrint) override;
    void print(size_t valueToPrint) override;
    std::string str() const;

private:
    std::ostringstream stream_;
};
