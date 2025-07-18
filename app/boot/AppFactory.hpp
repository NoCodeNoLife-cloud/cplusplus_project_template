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

        static const inline std::map<std::string, std::string> TYPE{
            {"console", coco::EnumUtil::getEnumClassName(AppType::ConsoleExecutor)},
            {"qt", coco::EnumUtil::getEnumClassName(AppType::QtExecutor)}
        };

    private:
        auto registerAll() -> void override;
    };
}
