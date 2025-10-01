#pragma once
#include <boost/uuid/uuid.hpp>
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
}
