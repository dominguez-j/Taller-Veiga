#include "wordscounter.h"

#include <string.h>

#define DELIM_WORDS " ,.;:\n"

Wordscounter::Wordscounter() { this->words = 0; }

size_t Wordscounter::get_words() { return this->words; }

bool Wordscounter::is_a_delimiter(char c) { return strchr(DELIM_WORDS, c) != nullptr; }

void Wordscounter::process(std::istream& text_file) {
    bool in_word = false;
    char c;

    while (text_file.get(c)) {
        if (is_a_delimiter(c)) {
            in_word = false;
        } else {
            if (!in_word) {
                in_word = true;
                words++;
            }
        }
    }
}
