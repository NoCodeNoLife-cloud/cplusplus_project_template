#pragma once
#include <boost/type_index.hpp>

namespace common {
class ClassUtil abstract {
 public:
  ClassUtil() = delete;

  template <typename T>
  static auto getTypeId(const T& t) -> std::string;

  template <typename T>
  static auto getTypeIdWithCvr(const T& t) -> std::string;

  template <typename T>
  static auto getTypeIdByClass() -> std::string;

  template <typename T>
  static auto getTypeIdWithCvrByClass(const std::string& t) -> std::string;
};

template <typename T>
auto ClassUtil::getTypeId(const T&) -> std::string {
  return boost::typeindex::type_id<T>().pretty_name();
}

template <typename T>
auto ClassUtil::getTypeIdWithCvr(const T&) -> std::string {
  return boost::typeindex::type_id_with_cvr<T>().pretty_name();
}

template <typename T>
auto ClassUtil::getTypeIdByClass() -> std::string {
  return boost::typeindex::type_id<T>().pretty_name();
}

template <typename T>
auto ClassUtil::getTypeIdWithCvrByClass(const std::string& t) -> std::string {
  return boost::typeindex::type_id_with_cvr<T>().pretty_name();
}
}  // namespace common
