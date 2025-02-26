//
// Created by lepag on 2/25/2025.
//

#ifndef APYINTERP_H
#define APYINTERP_H

#include <Python.h>
#include <string>

namespace tri::py {
    class APyInterp {
    public:
        APyInterp();
        ~APyInterp();

        void Py(const std::string &scriptPath) const;

    private:
        PyThreadState *state;
    };
} // py
// tri

#endif //APYINTERP_H
