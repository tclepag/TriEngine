//
// Created by lepag on 2/24/25.
//

#ifndef ALUAINTEGER_H
#define ALUAINTEGER_H

namespace tri::lua {
    class ALuaInteger {
        public:
        ALuaInteger(int value) {
            this->value = value ? value : 0;
        };
        ALuaInteger& operator=(const int value) {
            this->value = value;
            return *this;
        };
    protected:
        int value;
    };
}

#endif //ALUAINTEGER_H
