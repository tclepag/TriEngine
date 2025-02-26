//
// Created by lepag on 2/25/25.
//

#ifndef PYCORE_H
#define PYCORE_H


#include <Python.h>
#include <pybind11/pybind11.h>

#include "../py/APyManager.h"
#include "../common/EventDispatcher.h"

using namespace tri::common;
using namespace tri::py;

namespace tri::core {

class PyCore {
public:
    PyCore(const PyCore&) = delete;
    PyCore& operator=(const PyCore&) = delete;

    static PyCore* GetCore() {
        auto* Py = Instance;
        if (Py == nullptr) {
            Py = new PyCore();
            Instance = Py;
        }
        return Py;
    }

    void Start();
    void Stop() const;
private:
    static PyCore* Instance;
    PyCore();
    ~PyCore();
};

} // core
// tri

#endif //PYCORE_H
