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
        /// @brief Generates a random UUID string.
        /// @return A string representation of the generated UUID.
        // ReSharper disable once CppDFAConstantFunctionResult
        static auto GenerateRandomUuid() -> std::string
        {
            static auto generator = boost::uuids::random_generator();
            return boost::uuids::to_string(generator());
        }
    };
} // namespace fox
