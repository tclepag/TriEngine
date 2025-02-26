//
// Created by lepag on 2/25/2025.
//

#ifndef APYMANAGER_H
#define APYMANAGER_H

#include <vector>
#include "APyInterp.h"

namespace tri::py {
    class APyManager {
    public:
        using Interpreter = std::shared_ptr<APyInterp>;
        APyManager(const APyManager&) = delete;
        APyManager& operator=(const APyManager&) = delete;

        APyInterp* CreateInterpreter(const char* Name);
        void DestroyInterpreter(Interpreter* Interpreter);

        Interpreter& operator[](const char* Name);

        static APyManager& GetManager() {
            static APyManager* instance = Instance;
            if (instance == nullptr) {
                instance = new APyManager();
            }
            return *instance;
        }

        void Free() {
            delete this;
        }
    private:
        APyManager();
        ~APyManager();

        std::unordered_map<const char*, Interpreter> Intrepreters;
        static APyManager* Instance;
    };
}



#endif //APYMANAGER_H
