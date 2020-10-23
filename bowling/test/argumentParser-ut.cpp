#include <gtest/gtest.h>

#include "argumentParser.hpp"

struct ArgumentParserTestFixture : public ::testing::Test {
    char appName[10] = "./bowling";
    char inputDir[9] = "inputDir";
    char outputFileName[15] = "outputFileName";
    char helpArgLong[7] = "--help";
    char helpArgShort[3] = "-h";
    char additionalArgument[5] = "argX";

    char* noArgsAppCall[1] = {appName};
    size_t noArgsAppCallCnt = 1;

    char* onlyInputDirAppCall[2] = {appName, inputDir};
    size_t onlyInputDirAppCallCnt = 2;

    char* bothDirAndFileAppCall[3] = {appName, inputDir, outputFileName};
    size_t bothDirAndFileAppCallCnt = 3;
};

TEST_F(ArgumentParserTestFixture, shouldBeInitializedWithGivenAppName) {
    // GIVEN
    ArgumentParser ap{noArgsAppCallCnt, noArgsAppCall};

    // WHEN
    auto result = ap.getAppName();

    // THEN
    ASSERT_EQ(result, appName);
}

TEST_F(ArgumentParserTestFixture, inputDirectoryAndOutputFileNameStringsShouldBeEmptyWhenNoArgumentsWereGiven) {
    // GIVEN
    ArgumentParser ap{noArgsAppCallCnt, noArgsAppCall};

    // WHEN
    auto inputDirectory = ap.getInputDirectory();
    auto outputFileName = ap.getOutputFileName();
    auto result = inputDirectory.empty() && outputFileName.empty();

    // THEN
    ASSERT_TRUE(result);
}

TEST_F(ArgumentParserTestFixture, outputFileNameStringShouldBeEmptyWhenOnlyInputDirectoryWasGiven) {
    // GIVEN
    ArgumentParser ap{onlyInputDirAppCallCnt, onlyInputDirAppCall};

    // WHEN
    auto result = ap.getOutputFileName();

    // THEN
    ASSERT_EQ(result, "");
}

TEST_F(ArgumentParserTestFixture, inputDirectoryShouldBeInitializedWithGivenArgument) {
    // GIVEN
    ArgumentParser ap{onlyInputDirAppCallCnt, onlyInputDirAppCall};

    // WHEN
    auto result = ap.getInputDirectory();

    // THEN
    ASSERT_EQ(result, inputDir);
}

TEST_F(ArgumentParserTestFixture, inputDirectoryAndOutputFileNameShouldBeInitializedWithGivenArguments) {
    // GIVEN
    ArgumentParser ap{bothDirAndFileAppCallCnt, bothDirAndFileAppCall};

    // WHEN
    auto result = ap.getInputDirectory() == inputDir && ap.getOutputFileName() == outputFileName;

    // THEN
    ASSERT_TRUE(result);
}

TEST_F(ArgumentParserTestFixture, helpShouldBeCalledWhenNotEnoughArguments) {
    // GIVEN
    ArgumentParser ap{noArgsAppCallCnt, noArgsAppCall};

    // WHEN
    auto result = ap.isHelpNeeded();

    // THEN
    ASSERT_EQ(result, true);
}

TEST_F(ArgumentParserTestFixture, helpShouldBeCalledWhenTooMuchArguments) {
    // GIVEN
    char* argumentsArray[] = {appName, inputDir, outputFileName, additionalArgument};
    size_t argumentsCounter = sizeof(argumentsArray) / sizeof(char*);
    ArgumentParser ap{argumentsCounter, argumentsArray};

    // WHEN
    auto result = ap.isHelpNeeded();

    // THEN
    ASSERT_EQ(result, true);
}

TEST_F(ArgumentParserTestFixture, helpShouldBeCalledWhenShortHelpFlagUsed) {
    // GIVEN
    char* argumentsArray[] = {appName, helpArgShort};
    size_t argumentsCounter = sizeof(argumentsArray) / sizeof(char*);
    ArgumentParser ap{argumentsCounter, argumentsArray};

    // WHEN
    auto result = ap.isHelpNeeded();

    // THEN
    ASSERT_EQ(result, true);
}

TEST_F(ArgumentParserTestFixture, helpShouldBeCalledWhenLongHelpFlagUsed) {
    // GIVEN
    char* argumentsArray[] = {appName, helpArgLong};
    size_t argumentsCounter = sizeof(argumentsArray) / sizeof(char*);
    ArgumentParser ap{argumentsCounter, argumentsArray};

    // WHEN
    auto result = ap.isHelpNeeded();

    // THEN
    ASSERT_EQ(result, true);
}

TEST_F(ArgumentParserTestFixture, helpShouldNotBeCalledWhenSingleArgumentWasGiven) {
    // GIVEN
    ArgumentParser ap{onlyInputDirAppCallCnt, onlyInputDirAppCall};

    // WHEN
    auto result = ap.isHelpNeeded();

    // THEN
    ASSERT_EQ(result, false);
}

TEST_F(ArgumentParserTestFixture, helpShouldNotBeCalledWhenTwoArgumentsWereGiven) {
    // GIVEN
    ArgumentParser ap{bothDirAndFileAppCallCnt, bothDirAndFileAppCall};

    // WHEN
    auto result = ap.isHelpNeeded();

    // THEN
    ASSERT_EQ(result, false);
}
