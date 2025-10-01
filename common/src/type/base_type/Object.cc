#include "src/type/base_type/Object.hpp"

#include <format>
#include <typeinfo>

namespace fox
{
    auto Object::getClass() const noexcept -> const std::type_info&
    {
        return typeid(*this);
    }

    auto Object::hashCode() const noexcept -> size_t
    {
        return 0;
    }
}
