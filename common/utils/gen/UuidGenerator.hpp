#pragma once
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <string>

namespace fox
{
    /// @brief A utility class for generating UUIDs.
    /// This class provides functionality to generate random UUID strings.
    class UuidGenerator
    {
    public:
        UuidGenerator() = delete;

        /// @brief Generates a random UUID string.
        /// @return A string representation of the generated UUID.
        [[nodiscard]] static auto GenerateRandomUuid() noexcept -> std::string;
    };

    // ReSharper disable once CppDFAConstantFunctionResult
    inline auto UuidGenerator::GenerateRandomUuid() noexcept -> std::string
    {
        static auto generator = boost::uuids::random_generator();
        return boost::uuids::to_string(generator());
    }
}
