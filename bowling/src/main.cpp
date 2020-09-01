#include <algorithm>
#include <iostream>
#include <string>

#include "ArgumentParser.hpp"
#include "game.hpp"

void showHelp(std::string appName);

int main(int argc, char* argv[]) {
    ArgumentParser ap{argc, argv};

    if (ap.isHelpNeeded()) {
        showHelp(ap.getAppName());
        return 0;
    }

    auto inputDirectory = ap.getInputDirectory();
    auto outputFileName = ap.getOutputFileName();

    std::cout << "input dir: " << inputDirectory << "\n";
    std::cout << "output file: " << outputFileName << "\n";

    return 0;
}

void showHelp(std::string appName)
{
    std::cout << "Bowling game application reads text files from given directory, "
              << "calculates the game results and optionally saves the results to text file.\n\n"
              << "Application usage:\t" << appName << " <inputDirectory> [outputTextFile] [-h, --help]\n\n"
              << "Arguments:\n"
              << "\tinputDirectory\t\tMANDATORY: input directory with .txt files containing game scores\n"
              << "\toutputTextFile\t\tOPTIONAL: output .txt file to save processed results\n\n"
              << "Options:\n"
              << "\t-h,--help\t\tShow this help message\n"
              << std::endl;
}
