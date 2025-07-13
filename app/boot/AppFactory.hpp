#pragma once
#include "interface/IApplicationExecutor.hpp"
#include "type/util/ObjectFactory.hpp"

namespace app {

class AppFactory final :public coco::ObjectFactory<IApplicationExecutor> {
    auto registerAll() -> void override;
};

}
