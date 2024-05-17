#include "../src/program.cpp"
#include <gtest/gtest.h>
#include <fstream>
#include <sstream>

char *inputFile, *expectedFile;

void check() {
    try {
        std::stringstream& ss = runProgram(inputFile);
    } catch (std::string errMsg) {
        std::ifstream expected(expectedFile);
        std::string expectedLine;
        if (!getline(expected, expectedLine)) {
            throw "Неправильный ответ";
        }
        std::cout << expectedLine << ' ' << errMsg << '\n';
        if (expectedLine != errMsg || getline(expected, expectedLine)) {
            throw "Неправильный ответ";
        }
        return;
    } catch (double errNum) {
        std::ifstream expected(expectedFile);
        std::string expectedLine;
        if (!getline(expected, expectedLine)) {
            throw "Неправильный ответ";
        }
        try {
            double expectedNum = std::stof(expectedLine);
            std::cout << errNum << ' ' << expectedNum << '\n';
            if (fabs(expectedNum - errNum) > 1e-6) {
                throw "Неправильный ответ";
            }
            return;
        } catch (...) {
            throw "Неправильный ответ";
        }
    }

    std::ifstream expected(expectedFile);

    std::string lineGot, lineExpected;
    while (std::getline(ss, lineGot) && std::getline(expected, lineExpected)) { 
        if (lineGot != lineExpected) throw "Неправильный ответ";
    }
    if (std::getline(ss, lineGot) || std::getline(expected, lineExpected)) throw "Разные количества строк";
    return;
}

TEST(FileInputTest, ReadTestData) {
    ASSERT_NO_THROW(check());
}


int main(int argc, char* argv[]) {
    inputFile = argv[1];
    expectedFile = argv[2];
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
