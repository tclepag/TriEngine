//
// Created by lepag on 2/24/25.
//

#ifndef ALUATABLE_H
#define ALUATABLE_H
#include <string>
#include <unordered_map>

#include "ALuaBool.h"
#include "ALuaNumber.h"
#include "ALuaInteger.h"

namespace tri::lua {
    class ALuaTable {
        public:
        using TableValue = std::variant<ALuaBool, ALuaNumber, ALuaInteger>;
        ALuaTable();

        TableValue operator[](const std::string& key);
        {
            return std::visit([](auto&& arg) {
                return std::get<ALuaBool>(arg);
            });
        }
    protected:
        std::unordered_map<const char*, TableValue*> value;
    };
}

#endif //ALUATABLE_H
