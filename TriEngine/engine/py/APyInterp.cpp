//
// Created by lepag on 2/25/2025.
//

#include "APyInterp.h"


namespace tri::py {
    APyInterp::APyInterp(APyManager& manager): manager(manager) {
        state = Py_NewInterpreter();
        if (state == nullptr) {
            PyErr_SetString(PyExc_RuntimeError, "Failed to create interpreter");
            return;
        }
    }

    APyInterp::~APyInterp() {
        if (state != nullptr) {
            Py_EndInterpreter(state);
        }
    }

    void APyInterp::Py(const std::string &scriptPath) const {
        PyGILState_STATE gstate = PyGILState_Ensure();

        PyObject *script = PyRun_String(scriptPath.c_str(), Py_file_input, nullptr, nullptr);
        if (script == nullptr) {
            PyErr_SetString(PyExc_RuntimeError, "Failed to import script");
            return;
        }
        Py_XDECREF(state);
        PyGILState_Release(gstate);
    }

} // py
// tri