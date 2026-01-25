#pragma once
#include <string>
#include <unordered_map>
#include <format>
#include <boost/type_index.hpp>
#include <tuple>

namespace common::toolkit {
    template<typename T>
    struct ReflectTraits;

    /// @brief Utility class for type identification at runtime.
    /// This class provides a set of static methods to retrieve the type information
    /// of objects or classes using boost::typeindex. It is designed as a
    /// class with deleted constructor to prevent instantiation.
    class ClassToolkit {
    public:
        ClassToolkit() = delete;

        // ReSharper disable once CppDoxygenUnresolvedReference
        /// @brief Get the type id of the given object.
        /// @tparam T Type of the object.
        /// @param t The object to get type id from.
        /// @return std::string The pretty name of the type.
        template<typename T>
        [[nodiscard]] static auto getTypeId(const T & /*t*/) noexcept -> std::string {
            return boost::typeindex::type_id<T>().pretty_name();
        }

        // ReSharper disable once CppDoxygenUnresolvedReference
        /// @brief Get the type id with CVR (const, volatile, reference) of the given object.
        /// @tparam T Type of the object.
        /// @param t The object to get type id with CVR from.
        /// @return std::string The pretty name of the type with CVR.
        template<typename T>
        [[nodiscard]] static auto getTypeIdWithCvr(const T & /*t*/) noexcept -> std::string {
            return boost::typeindex::type_id_with_cvr<T>().pretty_name();
        }

        /// @brief Get the type id by class type.
        /// @tparam T Type of the class.
        /// @return std::string The pretty name of the type.
        template<typename T>
        [[nodiscard]] static auto getTypeIdByClass() noexcept -> std::string {
            return boost::typeindex::type_id<T>().pretty_name();
        }

        /// @brief Get the type id with CVR by class type.
        /// @tparam T Type of the class.
        /// @return std::string The pretty name of the type with CVR.
        template<typename T>
        [[nodiscard]] static auto getTypeIdWithCvrByClass() noexcept -> std::string {
            return boost::typeindex::type_id_with_cvr<T>().pretty_name();
        }

        /// @brief Get the fields of the given object.
        /// @tparam T Type of the object.
        /// @param obj The object to get fields from.
        /// @return std::unordered_map<std::string, std::string> A map of field names to their string representations.
        template<typename T>
        [[nodiscard]] static auto getFields(const T &obj) -> std::unordered_map<std::string, std::string> {
            std::unordered_map<std::string, std::string> field_map;
            constexpr auto fields = ReflectTraits<T>::fields;

            // Process each field using index-based access
            [&obj, &field_map, fields]<std::size_t... Is>(std::index_sequence<Is...>) {
                ((field_map.insert(std::make_pair(std::get<Is>(fields).first, std::format("{}", invokeHelper(obj, std::get<Is>(fields).second))))), ...);
            }(std::make_index_sequence<ReflectTraits<T>::field_count>{});

            return field_map;
        }

    private:
        /// @brief Helper function to invoke member pointers.
        /// @tparam T Type of the object.
        /// @tparam M Type of the member pointer.
        /// @param obj The object to invoke the member pointer on.
        /// @param member The member pointer.
        /// @return The result of invoking the member pointer.
        template<typename T, typename M>
        [[nodiscard]] static auto invokeHelper(const T &obj, M member) -> decltype(obj.*member) {
            return obj.*member;
        }

        /// @brief Helper function to invoke member functions.
        /// @tparam T Type of the object.
        /// @tparam M Type of the member function pointer.
        /// @param obj The object to invoke the member function on.
        /// @param member The member function pointer.
        /// @return The result of invoking the member function.
        template<typename T, typename M>
        [[nodiscard]] static auto invokeHelper(const T &obj, M member) -> decltype((obj.*member)()) {
            return (obj.*member)();
        }
    };
}
