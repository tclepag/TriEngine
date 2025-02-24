//
// Created by lepag on 2/24/25.
//

#ifndef ALUANUMBER_H
#define ALUANUMBER_H
#include <variant>

namespace tri::lua {
    class ALuaNumber {
        public:
        using LuaNumber = std::variant<float, double>;
        explicit ALuaNumber(LuaNumber value) {
            this->value = value ? value : 0.0;
        }

        [[nodiscard]] LuaNumber Get() const {
            return this->value;
        }

        ALuaNumber& operator=(LuaNumber value) {
            this->value = value;
            return *this;
        }
    protected:
        LuaNumber value;
    };
}

#endif //ALUANUMBER_H
