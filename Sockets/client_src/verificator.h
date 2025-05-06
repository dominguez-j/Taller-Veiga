#ifndef __VERIFICATOR_H__
#define __VERIFICATOR_H__

#include <string>
#include <unordered_set>

class Verificator {
private:
    static const std::unordered_set<std::string> valid_weapons;
    static const std::unordered_set<std::string> valid_commands;

public:
    /*
     * `Verificator::verificate_operation` verifica si la
     * operación es válida.
     * */
    static bool verificate_operation(const std::string& message);
};

#endif  // __VERIFICATOR_H__
