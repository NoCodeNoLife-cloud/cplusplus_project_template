#pragma once
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace fox
{
    /// @class JsonObjectSerializer
    /// @brief A utility class for serializing and deserializing JSON objects using RapidJSON.
    /// This class provides static methods to extract values from JSON objects with default fallbacks
    /// and to serialize fields to JSON format.
    class JsonObjectSerializer
    {
    public:
        /// @brief Gets a string value from JSON or returns a default value.
        /// @param json The JSON object to extract the value from.
        /// @param key The key of the value to extract.
        /// @param defaultValue The default value to return if key is not found or not a string.
        /// @return The extracted string value or the default value.
        [[nodiscard]] static auto getStringOrDefault(const rapidjson::Value& json, const char* key,
                                                     const std::string& defaultValue) noexcept -> std::string;

        /// @brief Gets an integer value from JSON or returns a default value.
        /// @param json The JSON object to extract the value from.
        /// @param key The key of the value to extract.
        /// @param defaultValue The default value to return if key is not found or not an integer.
        /// @return The extracted integer value or the default value.
        [[nodiscard]] static auto getIntOrDefault(const rapidjson::Value& json, const char* key,
                                                  int32_t defaultValue) noexcept -> int32_t;

        /// @brief Gets a double value from JSON or returns a default value.
        /// @param json The JSON object to extract the value from.
        /// @param key The key of the value to extract.
        /// @param defaultValue The default value to return if key is not found or not a double.
        /// @return The extracted double value or the default value.
        [[nodiscard]] static auto getDoubleOrDefault(const rapidjson::Value& json, const char* key,
                                                     double defaultValue) noexcept -> double;

        /// @brief Gets a boolean value from JSON or returns a default value.
        /// @param json The JSON object to extract the value from.
        /// @param key The key of the value to extract.
        /// @param defaultValue The default value to return if key is not found or not a boolean.
        /// @return The extracted boolean value or the default value.
        [[nodiscard]] static auto getBoolOrDefault(const rapidjson::Value& json, const char* key,
                                                   bool defaultValue) noexcept -> bool;

        /// @brief Serializes a string field to JSON.
        /// @param writer The JSON writer to use for serialization.
        /// @param key The key for the field.
        /// @param value The string value to serialize.
        static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key,
                                   const std::string& value) noexcept -> void;

        /// @brief Serializes an integer field to JSON.
        /// @param writer The JSON writer to use for serialization.
        /// @param key The key for the field.
        /// @param value The integer value to serialize.
        static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key,
                                   int32_t value) noexcept -> void;

        /// @brief Serializes a double field to JSON.
        /// @param writer The JSON writer to use for serialization.
        /// @param key The key for the field.
        /// @param value The double value to serialize.
        static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key,
                                   double value) noexcept -> void;

        /// @brief Serializes a boolean field to JSON.
        /// @param writer The JSON writer to use for serialization.
        /// @param key The key for the field.
        /// @param value The boolean value to serialize.
        static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key,
                                   bool value) noexcept -> void;
    };
}
