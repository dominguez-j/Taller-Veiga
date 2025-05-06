#ifndef __TEXT_SPLITTER_H__
#define __TEXT_SPLITTER_H__

#include <string>
#include <vector>

#define SPACE ' '
#define END_OF_LINE '\n'
#define EMPTY_MSG ""
#define COMMA ','
#define COLON ':'
#define DOT '.'

class TextSplitter {
public:
    /*
     * `TextSplitter::split_text` divide un string en partes
     * separadas por el delimitador dado.
     *
     * Devuelve un vector de strings con las partes.
     * */
    static std::vector<std::string> split_text(const std::string& input, char delimiter);
};

#endif  // __TEXT_SPLITTER_H__
