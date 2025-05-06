#include <fstream>
#include <iostream>
#include <string>

#include "wordscounter.h"

enum Codes {
    SUCCESS,
    ERROR,
};

int main(int argc, char* argv[]) {
    Wordscounter counter;

    if (argc > 1) {
        std::ifstream input(argv[1]);
        if (!input.is_open()) {
            return ERROR;
        }
        counter.process(input);
    } else {
        counter.process(std::cin);
    }
    size_t words = counter.get_words();
    std::cout << words << std::endl;
    return SUCCESS;
}
