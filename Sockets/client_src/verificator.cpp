#include "verificator.h"

#include "../common_src/converter.h"
#include "../common_src/data.h"
#include "../common_src/text_splitter.h"

#define NUM_ARGS_MAX 3
#define NUM_ARGS_MIN 2

const std::unordered_set<std::string> Verificator::valid_weapons = {M3, AWP, AK47, GLOCK};
const std::unordered_set<std::string> Verificator::valid_commands = {BUY, AMMO};

bool Verificator::verificate_operation(const std::string& message) {
    auto splitted_message = TextSplitter::split_text(message, SPACE);

    int size = splitted_message.size();
    if (size > NUM_ARGS_MAX or size < NUM_ARGS_MIN)
        return false;

    if ((valid_commands.count(splitted_message[0]) == 0) or
        (valid_weapons.count(splitted_message[1]) == 0))
        return false;

    if (size == 3 and std::stoi(splitted_message[2]) < 0)
        return false;

    return true;
}
