//
// Created by lepag on 2/24/25.
//

#ifndef ALUABOOL_H
#define ALUABOOL_H

namespace tri::lua {
    class ALuaBool {
    public:
        ALuaBool(bool value) {
            this->value = value ? value : true;
        };

        [[nodiscard]] bool Get() const {
            return value;
        };

        ALuaBool& operator=(const bool& value) {
            this->value = value;
            return *this;
        }

    private:
        bool value;
    };
}

#endif //ALUABOOL_H
