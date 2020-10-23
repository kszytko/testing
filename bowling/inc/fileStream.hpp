#pragma once

#include "printerStream.hpp"

#include <fstream>
#include <string>

class FileStream : public PrinterStream {
public:
    FileStream(const std::string& filePath);
    ~FileStream();

    void print(const std::string& stringToPrint) override;
    void print(size_t valueToPrint) override;

private:
    std::ofstream* file_;
};
