//
// Created by lepag on 2/26/25.
//

#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H
#include <functional>


namespace tri::common {
    template<typename  ...Args>
    class EventDispatcher {
    public:
        EventDispatcher() = default;
        ~EventDispatcher() = default;

        void in(std::function<void(Args...)> fun) {
            listeners.emplace_back(fun);
        }

        void out(Args... args) {
            for (auto fun: listeners) {
                fun(args...);
            }
        }
    private:
        std::vector<std::function<void(Args...)>> listeners;
    };
}



#endif //EVENTDISPATCHER_H
