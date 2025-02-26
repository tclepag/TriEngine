//
// Created by lepag on 2/26/2025.
//

#ifndef DELEGATE_H
#define DELEGATE_H

#include <functional>
#include <vector>
#include <memory>

namespace tri::common {
    template <typename ...Args>
class Delegate {
public:
        using Func = std::function<void(Args...)>;
    using Callback = std::shared_pointer<Func>;

        ~Delegate() {
            for (auto& listener : listeners) {
                listener.reset();
            }
        }

        void Invoke(Args... args) {
            for (auto& listener : listeners) {
                listener(args);
            }
        }

        Callback Append(Func listener) {
            listeners.emplace_back(std::make_shared<Func>(listener));
        }

        void Remove(Callback lstnr) {
            for (auto& listener : listeners) {
                if (listener == lstnr) {
                    listener.reset();
                }
            }
            return nullptr;
        }
private:
    std::vector<Callback> listeners
};

} // common
} // tri

#endif //DELEGATE_H
