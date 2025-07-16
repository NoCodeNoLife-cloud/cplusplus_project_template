#include "AppParameters.hpp"

namespace app
{
    auto AppParameters::appType(const std::string& app_type) -> void
    {
        app_type_ = app_type;
    }

    auto AppParameters::appType() const -> std::string
    {
        return app_type_;
    }
}
