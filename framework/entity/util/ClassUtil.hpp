#pragma once
#include <boost/type_index.hpp>

namespace framework::entity::util {
  class ClassUtil abstract {
  public:
    ClassUtil() = delete;
    template <typename T>
    static auto getTypeId(const T& t) -> std::string;
  };

  template <typename T>
  auto ClassUtil::getTypeId(const T& t) -> std::string {
    return boost::typeindex::type_id_with_cvr<decltype(t)>().pretty_name();
  }
} // namespace framework::entity::util
