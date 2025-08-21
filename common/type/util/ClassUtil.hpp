#pragma once
#include <boost/type_index.hpp>

namespace common {
/// @brief Utility class for type identification at runtime.
/// This class provides a set of static methods to retrieve the type information
/// of objects or classes using boost::typeindex. It is designed as an
/// class with deleted constructor to prevent instantiation.
class ClassUtil {
 public:
  ClassUtil() = delete;

  /// @brief Get the type id of the given object.
  /// @tparam T Type of the object.
  /// @param t The object to get type id from.
  /// @return std::string The pretty name of the type.
  template <typename T>
  static auto getTypeId(const T& t) -> std::string;

  /// @brief Get the type id with CVR (const, volatile, reference) of the given object.
  /// @tparam T Type of the object.
  /// @param t The object to get type id with CVR from.
  /// @return std::string The pretty name of the type with CVR.
  template <typename T>
  static auto getTypeIdWithCvr(const T& t) -> std::string;

  /// @brief Get the type id by class type.
  /// @tparam T Type of the class.
  /// @return std::string The pretty name of the type.
  template <typename T>
  static auto getTypeIdByClass() -> std::string;

  /// @brief Get the type id with CVR by class type.
  /// @tparam T Type of the class.
  /// @param t Placeholder parameter, not used in implementation.
  /// @return std::string The pretty name of the type with CVR.
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
auto ClassUtil::getTypeIdWithCvrByClass(const std::string&) -> std::string {
  return boost::typeindex::type_id_with_cvr<T>().pretty_name();
}
}  // namespace common
