#include <iostream>
#include <boot/Startup.hpp>
#include <service/BoolFunctorRegister.hpp>

namespace common
{
    Startup::Startup()
    {
        runAll();
    }

    void Startup::runAll()
    {
        for (const auto& func : BoolFunctorRegister::getRegisteredFunctions())
        {
            if (!func())
            {
                std::cerr << "Function not registered";
                return;
            }
        }
    }
}
