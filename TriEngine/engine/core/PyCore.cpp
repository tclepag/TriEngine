//
// Created by lepag on 2/25/25.
//

#include "PyCore.h"


namespace tri::core {
    PyCore* PyCore::Instance = nullptr;

    PyCore::PyCore() = default;

    void PyCore::Start() {
        if (!Py_IsInitialized()) {
            Py_Initialize();
        }
    }

    void PyCore::Stop() const {
        delete this;
    }

    PyCore::~PyCore() {
        if (Py_IsInitialized()) {
            Py_Finalize();
        }
    }


} // core
// tri