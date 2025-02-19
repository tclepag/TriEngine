//
// Created by lepag on 2/18/2025.
//

#ifndef TIME_H
#define TIME_H

#include <windows.h>

namespace tri::util {

    class Time final {
    public:
        static double GetElapsedTime(); // Returns time since application started

        Time() {
            Initialize();
        }

        Time(Time&&) = delete;
        Time& operator=(Time&&) = delete;
    private:
        LARGE_INTEGER start{};
        LARGE_INTEGER frequency{};

        void Initialize();
        static Time* instance;
    };

}

#endif //TIME_H
