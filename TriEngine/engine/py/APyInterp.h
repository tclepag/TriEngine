//
// Created by lepag on 2/25/2025.
//

#ifndef APYINTERP_H
#define APYINTERP_H

#include <Python.h>
#include <string>

namespace tri::py {
    class APyManager;
    class APyInterp {
    public:
        APyInterp(APyManager& manager);
        ~APyInterp();

        void SetCurrent();
        void Py(const std::string &scriptPath) const;

    private:
        APyManager& manager;
        PyThreadState *state;
    };
} // py
// tri

#endif //APYINTERP_H
