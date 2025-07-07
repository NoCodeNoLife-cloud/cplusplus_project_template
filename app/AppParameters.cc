#include <AppParameters.hpp>

namespace app
{
    AppParameters::AppParameters() = default;
    AppParameters::~AppParameters() = default;
    AppParameters::AppParameters(const AppParameters& other) = default;
    AppParameters& AppParameters::operator=(const AppParameters& other) = default;
    AppParameters::AppParameters(AppParameters&& other) noexcept = default;

    auto AppParameters::appType(const std::string& app_type)
    {
        app_type_ = app_type;
    }

    auto AppParameters::appType() const -> std::string
    {
        return app_type_;
    }
}
