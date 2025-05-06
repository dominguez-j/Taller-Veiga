#include "text_splitter.h"

#include <sstream>

std::vector<std::string> TextSplitter::split_text(const std::string& input, char delimiter) {
    std::stringstream ss(input);
    std::vector<std::string> input_splitted;
    std::string segment;

    while (std::getline(ss, segment, delimiter)) input_splitted.push_back(segment);

    return input_splitted;
}
