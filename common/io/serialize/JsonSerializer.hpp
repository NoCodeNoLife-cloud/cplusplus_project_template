#pragma once
#include <fstream>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include "io/interface/IfaceJsonSerializable.hpp"

namespace common::io::serialize {
template <typename T>concept DerivedFromJsonSerializable = std::is_base_of_v<iface::IfaceJsonSerializable, T>;

/// \brief Class JsonSerializer abstract
/// \details This class is an abstract class which provides static methods to serialize and deserialize objects to and
/// from JSON files. It is used by the Student class to save and load student objects to and from JSON files.
class JsonSerializer abstract {
public:
  JsonSerializer() = delete;

  /// \brief Saves a student object to a JSON file.
  /// \tparam T type of the student object, must be derived from JsonSerializable.
  /// \param entity the student object to be saved.
  /// \param filename the name of the file to save.
  template <DerivedFromJsonSerializable T>
  static auto saveStudentToJsonFile(const T& entity, const std::string& filename) -> void {
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

  /// \brief Loads a student object from a JSON file.
  /// \tparam T type of the student object, must be derived from JsonSerializable.
  /// \param filename the name of the file to load.
  /// \return the loaded student object.
  template <DerivedFromJsonSerializable T>
  static auto loadStudentFromJsonFile(const std::string& filename) -> T {
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

  /// \brief Get a string value from a JSON object with a default value.
  /// \param json the JSON object to retrieve the value from.
  /// \param key the key to retrieve the value for.
  /// \param defaultValue the default value to return if the key doesn't exist or is not a string.
  /// \return the retrieved string value, or the default value if the key doesn't exist or is not a string.
  static auto getStringOrDefault(const rapidjson::Value& json, const char* key, const std::string& defaultValue) -> std::string {
    if (json.HasMember(key) && json[key].IsString()) {
      return json[key].GetString();
    }
    return defaultValue;
  }

  /// \brief Get an integer value from a JSON object with a default value.
  /// \param json the JSON object to retrieve the value from.
  /// \param key the key to retrieve the value for.
  /// \param defaultValue the default value to return if the key doesn't exist or is not an integer.
  /// \return the retrieved integer value, or the default value if the key doesn't exist or is not an integer.
  static auto getIntOrDefault(const rapidjson::Value& json, const char* key, const int defaultValue) -> int {
    if (json.HasMember(key) && json[key].IsInt()) {
      return json[key].GetInt();
    }
    return defaultValue;
  }

  /// \brief Get a double value from a JSON object with a default value.
  /// \param json the JSON object to retrieve the value from.
  /// \param key the key to retrieve the value for.
  /// \param defaultValue the default value to return if the key doesn't exist or is not a double.
  /// \return the retrieved double value, or the default value if the key doesn't exist or is not a double.
  static auto getDoubleOrDefault(const rapidjson::Value& json, const char* key, const double defaultValue) -> double {
    if (json.HasMember(key) && json[key].IsDouble()) {
      return json[key].GetDouble();
    }
    return defaultValue;
  }

  /// \brief Get a boolean value from a JSON object with a default value.
  /// \param json the JSON object to retrieve the value from.
  /// \param key the key to retrieve the value for.
  /// \param defaultValue the default value to return if the key doesn't exist or is not a boolean.
  /// \return the retrieved boolean value, or the default value if the key doesn't exist or is not a boolean.
  static auto getBoolOrDefault(const rapidjson::Value& json, const char* key, const bool defaultValue) -> bool {
    if (json.HasMember(key) && json[key].IsBool()) {
      return json[key].GetBool();
    }
    return defaultValue;
  }

  /// \brief Serialize a field into a JSON object.
  /// \param writer the JSON writer to use.
  /// \param key the key of the field.
  /// \param value the value of the field.
  static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const std::string& value) -> void {
    writer.Key(key);
    writer.String(value.c_str());
  }

  /// \brief Serialize a field into a JSON object.
  /// \param writer the JSON writer to use.
  /// \param key the key of the field.
  /// \param value the value of the field.
  /// \details This function serializes a field into a JSON object. It takes a JSON writer and a key-value pair as
  /// parameter. The key is the name of the field in the JSON object and the value is the value of that field. The JSON
  /// writer is used to write the key-value pair into the JSON object.
  static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const int value) -> void {
    writer.Key(key);
    writer.Int(value);
  }

  /// \brief Serialize a field into a JSON object.
  /// \param writer the JSON writer to use.
  /// \param key the key of the field.
  /// \param value the value of the field.
  /// \details This function serializes a field into a JSON object. It takes a JSON writer and a key-value pair as
  /// parameter. The key is the name of the field in the JSON object and the value is the value of that field. The JSON
  /// writer is used to write the key-value pair into the JSON object.
  static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const double value) -> void {
    writer.Key(key);
    writer.Double(value);
  }

  /// \brief Serialize a field into a JSON object.
  /// \param writer the JSON writer to use.
  /// \param key the key of the field.
  /// \param value the value of the field.
  /// \details This function serializes a field into a JSON object. It takes a JSON writer and a key-value pair as
  /// parameter. The key is the name of the field in the JSON object and the value is the value of that field. The JSON
  /// writer is used to write the key-value pair into the JSON object.
  static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const bool value) -> void {
    writer.Key(key);
    writer.Bool(value);
  }
};
}
