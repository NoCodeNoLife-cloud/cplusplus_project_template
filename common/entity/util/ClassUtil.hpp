#pragma once
#include <boost/type_index.hpp>

namespace common::entity::util
{
    class ClassUtil abstract
    {
    public:
        template <typename T> static std::string getTypeId(T t);
    };

    template <typename T> std::string ClassUtil::getTypeId([[maybe_unused]] T t)
    {
        return boost::typeindex::type_id_with_cvr<decltype(t)>().pretty_name();
    }
}
