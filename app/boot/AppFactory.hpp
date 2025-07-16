#pragma once
#include <map>
#include <magic_enum/magic_enum.hpp>

#include "interface/IApplicationExecutor.hpp"
#include "type/util/ObjectFactory.hpp"

namespace app
{
    class AppFactory final : public coco::ObjectFactory<IApplicationExecutor>
    {
    public:
        enum class AppType
        {
            ConsoleExecutor,
            QtExecutor
        };

        static const inline std::map<std::string, std::string> TYPE{
            {"console", static_cast<std::string>(magic_enum::enum_name(AppType::ConsoleExecutor))},
            {"qt", static_cast<std::string>(magic_enum::enum_name(AppType::QtExecutor))}
        };

    private:
        auto registerAll() -> void override;
    };
}
