#pragma once
#include <map>

#include "interface/IApplicationExecutor.hpp"
#include "type/util/EnumUtil.hpp"
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

        static const inline std::string CONSOLE_EXECUTOR_NAME = coco::EnumUtil::getEnumClassName(AppType::ConsoleExecutor);
        static const inline std::string QT_EXECUTOR_NAME = coco::EnumUtil::getEnumClassName(AppType::QtExecutor);
        static const inline std::unordered_map<std::string, std::string> TYPE{
            {"console", CONSOLE_EXECUTOR_NAME},
            {"qt", QT_EXECUTOR_NAME}
        };

    private:
        auto registerAll() -> void override;
    };
}
