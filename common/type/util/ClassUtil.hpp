#pragma once
#include <boost/type_index.hpp>

namespace common {
template <typename T>
struct ReflectTraits;

/*
 * template<>
 * struct common::ReflectTraits<Employee> {
 *     static constexpr auto fields = std::make_tuple(
 *         std::make_pair("name", &Employee::getName),
 *         std::make_pair("id", &Employee::getId),
 *         std::make_pair("salary", &Employee::getSalary)
 *     );
 *
 *     static constexpr std::size_t field_count = 3;
 * };
 */

/// @brief Utility class for type identification at runtime.
/// This class provides a set of static methods to retrieve the type information
/// of objects or classes using boost::typeindex. It is designed as a
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

  /// @brief Print the fields of a reflectable object.
  /// This function prints the name and value of each field in the given object.
  /// It uses the ReflectTraits to get the field information and the invoke_helper
  /// to get the field values.
  /// @tparam T Type of the object.
  /// @param obj The object whose fields are to be printed.
  template <typename T>
  static void print_fields(const T& obj);

 private:
  /// @brief Helper function to invoke member pointers.
  /// @tparam T Type of the object.
  /// @tparam M Type of the member pointer.
  /// @param obj The object to invoke the member pointer on.
  /// @param member The member pointer.
  /// @return The result of invoking the member pointer.
  template <typename T, typename M>
  static auto invoke_helper(const T& obj, M member) -> decltype(obj.*member);

  /// @brief Helper function to invoke member functions.
  /// @tparam T Type of the object.
  /// @tparam M Type of the member function pointer.
  /// @param obj The object to invoke the member function on.
  /// @param member The member function pointer.
  /// @return The result of invoking the member function.
  template <typename T, typename M>
  static auto invoke_helper(const T& obj, M member) -> decltype((obj.*member)());
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

template <typename T>
void ClassUtil::print_fields(const T& obj) {
  constexpr auto fields = ReflectTraits<T>::fields;

  // Print each field using index-based access
  [&obj, fields]<std::size_t... Is>(std::index_sequence<Is...>) { ((std::cout << "Field: " << std::get<Is>(fields).first << " = " << invoke_helper(obj, std::get<Is>(fields).second) << "\n"), ...); }(std::make_index_sequence<ReflectTraits<T>::field_count>{});
}

template <typename T, typename M>
auto ClassUtil::invoke_helper(const T& obj, M member) -> decltype(obj.*member) {
  return obj.*member;
}

template <typename T, typename M>
auto ClassUtil::invoke_helper(const T& obj, M member) -> decltype((obj.*member)()) {
  return (obj.*member)();
}
}  // namespace common
