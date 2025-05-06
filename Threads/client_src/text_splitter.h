#ifndef TEXT_SPLITTER_H
#define TEXT_SPLITTER_H

#include <string>
#include <vector>

#define SPACE ' '
#define END_OF_LINE '\n'
#define EMPTY_MSG ""
#define COMMA ','
#define COLON ':'
#define DOT '.'

class TextSplitter {
private:
    TextSplitter(const TextSplitter&) = delete;
    TextSplitter& operator=(const TextSplitter&) = delete;

public:
    TextSplitter() = default;

    std::vector<std::string> split_text(const std::string& input, char delimiter);

    TextSplitter(TextSplitter&&) = default;
    TextSplitter& operator=(TextSplitter&&) = default;

    ~TextSplitter() = default;
};

#endif  // TEXT_SPLITTER_H
