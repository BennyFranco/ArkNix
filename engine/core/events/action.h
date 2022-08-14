#ifndef ACTION_H
#define ACTION_H

#include <functional>
#include <vector>

// Reference https://www.geeksforgeeks.org/variadic-function-templates-c/
namespace nim {
    template<typename... T>
    class Action {
    public:
        void AddListener(std::function<void(T...)> callback) {
            callbackFunctions.emplace_back(callback);
        }
        void RemoveListener(std::function<void(T...)> callback) {
            callbackFunctions.erase(callback);
        }
        void Invoke(T... args) {
            for (auto func: callbackFunctions) {
                func(args...);
            }
        }

    private:
        std::vector<std::function<void(T...)>> callbackFunctions;
    };
}// namespace nim

#endif// ACTION_H