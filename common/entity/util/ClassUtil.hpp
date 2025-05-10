#pragma once
#include <boost/type_index.hpp>

namespace common {
  class ClassUtil abstract {
  public:
    ClassUtil() = delete;
    template <typename T>
    static auto getTypeId(const T& t) -> std::string;
  };

  template <typename T>
  auto ClassUtil::getTypeId([[maybe_unused]] const T& t) -> std::string {
    return boost::typeindex::type_id_with_cvr<decltype(t)>().pretty_name();
  }
}
