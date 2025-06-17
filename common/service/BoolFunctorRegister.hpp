#pragma once
#include <functional>
#include <vector>

namespace common
{
    class BoolFunctorRegister
    {
    public:
        BoolFunctorRegister() = default;
        ~BoolFunctorRegister() = default;

        template <typename T>
        static void signup()
        {
            register_functions_.emplace_back(T());
        }


        static std::vector<std::function<bool()>> getRegisteredFunctions()
        {
            return register_functions_;
        }

    private:
        static inline std::vector<std::function<bool()>> register_functions_{};
    };
}
