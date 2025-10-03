#include "src/toolkit/ClassToolkit.hpp"

#include <boost/type_index.hpp>
#include <string>
#include <unordered_map>
#include <format>
#include <tuple>

namespace common
{
    template <typename T>
    auto ClassToolkit::getTypeId(const T&) noexcept -> std::string
    {
        return boost::typeindex::type_id<T>().pretty_name();
    }

    template <typename T>
    auto ClassToolkit::getTypeIdWithCvr(const T&) noexcept -> std::string
    {
        return boost::typeindex::type_id_with_cvr<T>().pretty_name();
    }

    template <typename T>
    auto ClassToolkit::getTypeIdByClass() noexcept -> std::string
    {
        return boost::typeindex::type_id<T>().pretty_name();
    }

    template <typename T>
    auto ClassToolkit::getTypeIdWithCvrByClass() noexcept -> std::string
    {
        return boost::typeindex::type_id_with_cvr<T>().pretty_name();
    }

    template <typename T>
    auto ClassToolkit::getFields(const T& obj) -> std::unordered_map<std::string, std::string>
    {
        std::unordered_map<std::string, std::string> field_map;
        constexpr auto fields = ReflectTraits<T>::fields;

        // Print each field using index-based access
        [&obj, &field_map, fields]<std::size_t... Is>(std::index_sequence<Is...>)
        {
            ((field_map.insert(std::make_pair(std::get<Is>(fields).first,
                                              std::format("{}", invokeHelper(obj, std::get<Is>(fields).second))))),
                ...);
        }(std::make_index_sequence<ReflectTraits<T>::field_count>{});

        return field_map;
    }

    template <typename T, typename M>
    auto ClassToolkit::invokeHelper(const T& obj, M member) -> decltype(obj.*member)
    {
        return obj.*member;
    }

    template <typename T, typename M>
    auto ClassToolkit::invokeHelper(const T& obj, M member) -> decltype((obj.*member)())
    {
        return (obj.*member)();
    }
}
