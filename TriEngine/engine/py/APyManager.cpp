//
// Created by lepag on 2/25/2025.
//

#include "APyManager.h"

#include "../common/EventDispatcher.h"
#include "../core/Engine.h"

namespace tri::py {
    APyManager* APyManager::Instance = nullptr;

    APyInterp* APyManager::CreateInterpreter(const char *Name) {
        const Interpreter Interp = std::make_shared<APyInterp>(*this);
        Interpreters[Name] = Interp;
        auto casted = dynamic_cast<APyInterp*>(Interp.get());
        return casted;
    }

    void APyManager::DestroyInterpreter(Interpreter Interpreter) {
        Interpreter.reset();
    }

    APyManager::Interpreter APyManager::operator[](const char *Name) {
        return Interpreters[Name];
    }

    APyManager::APyManager() {
        CreateInterpreter("Core");
        CreateInterpreter("Development");
        CreateInterpreter("Game");
    }

    APyManager::~APyManager() {
        for (auto [first, second]: Interpreters) {
            DestroyInterpreter(second);
        }
    }
}
