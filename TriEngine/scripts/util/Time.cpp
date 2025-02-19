//
// Created by lepag on 2/18/2025.
//

#include "Time.h"

namespace tri::util {
    Time* Time::instance = nullptr;

    void Time::Initialize() {
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&start);
        instance = this;
    }

    double Time::GetElapsedTime() {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        return static_cast<double>(now.QuadPart - instance->start.QuadPart) / instance->frequency.QuadPart;
    }


}
