#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>

#include "argumentParser.hpp"
#include "filesReader.hpp"
#include "frameParser.hpp"
#include "game.hpp"
#include "printer.hpp"
#include "scoreCounter.hpp"

void showHelp(std::string appName) {
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

int main(int argc, char* argv[]) {
    ArgumentParser ap{static_cast<size_t>(argc), argv};

    if (ap.isHelpNeeded()) {
        showHelp(ap.getAppName());
        return 0;
    }

    auto inputDirectory = ap.getInputDirectory();
    auto outputFileName = ap.getOutputFileName();


    FilesReader reader(inputDirectory);
    ScoreCounter score(reader);
    Printer(outputFileName).print(score);
 
    return 0;
}
