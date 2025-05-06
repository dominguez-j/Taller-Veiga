#include "verificator.h"

#define NUM_ARGS_MAX 3
#define NUM_ARGS_MIN 1

const bool Verificator::verificate_operation(const std::string& message) {
    auto splitted_message = txt_splitter.split_text(message, SPACE);

    int size = splitted_message.size();
    if (size > NUM_ARGS_MAX or size < NUM_ARGS_MIN)
        return false;

    if (valid_commands.find(splitted_message[0]) == valid_commands.end())
        return false;

    return true;
}
