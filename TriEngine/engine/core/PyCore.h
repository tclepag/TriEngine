//
// Created by lepag on 2/25/25.
//

#ifndef PYCORE_H
#define PYCORE_H

#include "../py/APyManager.h"
#include "../common/Delegation.h"
using namespace tri::common;
using namespace tri::py;

namespace tri::core {

class PyCore {
public:
    PyCore();
    ~PyCore();
private:
    APyManager* pyManager;
};

} // core
// tri

#endif //PYCORE_H
