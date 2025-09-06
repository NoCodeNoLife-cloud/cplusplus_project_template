#pragma once
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

#include <fstream>
#include <string>

#include "filesystem/io/interface/IJsonSerializable.hpp"

namespace fox {
/// @brief A utility class for serializing and deserializing objects to and from JSON format.
/// This class provides static methods for saving/loading objects that implement the IJsonSerializable interface,
/// as well as helper functions for reading primitive types from JSON with default value fallbacks
/// and for serializing primitive type fields into JSON format.
template <typename T>
concept DerivedFromJsonSerializable = std::is_base_of_v<IJsonSerializable, T>;

/// @brief A concept that checks if a type T is derived from IJsonSerializable
/// This concept is used to constrain template parameters in the JsonObjectSerializer class
/// to ensure that only types that implement the IJsonSerializable interface can be used
/// with the serialization and deserialization methods.
/// @tparam T The type to check
/// @return true if T is derived from IJsonSerializable, false otherwise
class JsonObjectSerializer {
 public:
  JsonObjectSerializer() = delete;

  /// @brief Save an object to a JSON file
  /// @tparam T Type of the object to save, must be derived from IJsonSerializable
  /// @param entity The object to save
  /// @param filename The path to the file where the JSON will be saved
  template <DerivedFromJsonSerializable T>
  static auto saveObjectToJsonFile(const T& entity, const std::string& filename) -> void;

  /// @brief Load an object from a JSON file
  /// @tparam T Type of the object to load, must be derived from IJsonSerializable
  /// @param filename The path to the JSON file to load
  /// @return The loaded object
  template <DerivedFromJsonSerializable T>
  static auto loadObjectFromJsonFile(const std::string& filename) -> T;

  /// @brief Get a string value from JSON or return a default value
  /// @param json The JSON value to search in
  /// @param key The key to look for
  /// @param defaultValue The default value to return if key is not found
  /// @return The string value if found, otherwise the default value
  static auto getStringOrDefault(const rapidjson::Value& json, const char* key, const std::string& defaultValue) -> std::string;

  /// @brief Get an integer value from JSON or return a default value
  /// @param json The JSON value to search in
  /// @param key The key to look for
  /// @param defaultValue The default value to return if key is not found
  /// @return The integer value if found, otherwise the default value
  static auto getIntOrDefault(const rapidjson::Value& json, const char* key, int32_t defaultValue) -> int32_t;

  /// @brief Get a double value from JSON or return a default value
  /// @param json The JSON value to search in
  /// @param key The key to look for
  /// @param defaultValue The default value to return if key is not found
  /// @return The double value if found, otherwise the default value
  static auto getDoubleOrDefault(const rapidjson::Value& json, const char* key, double defaultValue) -> double;

  /// @brief Get a boolean value from JSON or return a default value
  /// @param json The JSON value to search in
  /// @param key The key to look for
  /// @param defaultValue The default value to return if key is not found
  /// @return The boolean value if found, otherwise the default value
  static auto getBoolOrDefault(const rapidjson::Value& json, const char* key, bool defaultValue) -> bool;

  /// @brief Serialize a string field to JSON
  /// @param writer The JSON writer to use
  /// @param key The field key
  /// @param value The string value to serialize
  static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const std::string& value) -> void;

  /// @brief Serialize an integer field to JSON
  /// @param writer The JSON writer to use
  /// @param key The field key
  /// @param value The integer value to serialize
  static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, int32_t value) -> void;

  /// @brief Serialize a double field to JSON
  /// @param writer The JSON writer to use
  /// @param key The field key
  /// @param value The double value to serialize
  static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, double value) -> void;

  /// @brief Serialize a boolean field to JSON
  /// @param writer The JSON writer to use
  /// @param key The field key
  /// @param value The boolean value to serialize
  static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, bool value) -> void;
};

template <DerivedFromJsonSerializable T>
auto JsonObjectSerializer::saveObjectToJsonFile(const T& entity, const std::string& filename) -> void {
  rapidjson::StringBuffer buffer;
  rapidjson::PrettyWriter writer(buffer);
  entity.serialize(writer);
  std::ofstream ofs(filename);
  if (!ofs) {
    throw std::runtime_error("Failed to open file for writing: " + filename);
  }
  ofs << buffer.GetString();
  ofs.close();
}

template <DerivedFromJsonSerializable T>
auto JsonObjectSerializer::loadObjectFromJsonFile(const std::string& filename) -> T {
  T entity{};
  std::ifstream ifs(filename);
  if (!ifs) {
    throw std::runtime_error("Failed to open file for reading: " + filename);
  }
  const std::string jsonStr{std::istreambuf_iterator(ifs), std::istreambuf_iterator<char>()};
  ifs.close();
  rapidjson::Document document;
  if (document.Parse(jsonStr.c_str()).HasParseError()) {
    throw std::runtime_error("JSON parse error!");
  }
  if (document.IsObject()) {
    entity.deserialize(document);
  }
  return entity;
}
}  // namespace fox
