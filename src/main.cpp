#include "program.cpp"
#include <sstream>
#include <string>
#include <iostream>


int main(int argc, char *argv[]) {
    
    try {
        std::stringstream& ss = runProgram(argv[1]);

        std::string line;
        while (std::getline(ss, line)) std::cout << line << '\n';
    } catch (std::string errRow) {
        std::cout << errRow << '\n';
    }


    return 0;
}