#pragma once
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>

#include <fstream>
#include <string>

#include "filesystem/io/interface/IJsonSerializable.hpp"

namespace common {
template <typename T>
concept DerivedFromJsonSerializable = std::is_base_of_v<IJsonSerializable, T>;

class JsonObjectSerializer abstract {
 public:
  JsonObjectSerializer() = delete;
  template <DerivedFromJsonSerializable T>
  static auto saveObjectToJsonFile(const T& entity, const std::string& filename) -> void;
  template <DerivedFromJsonSerializable T>
  static auto loadObjectFromJsonFile(const std::string& filename) -> T;
  static auto getStringOrDefault(const rapidjson::Value& json, const char* key, const std::string& defaultValue) -> std::string;
  static auto getIntOrDefault(const rapidjson::Value& json, const char* key, int32_t defaultValue) -> int32_t;
  static auto getDoubleOrDefault(const rapidjson::Value& json, const char* key, double defaultValue) -> double;
  static auto getBoolOrDefault(const rapidjson::Value& json, const char* key, bool defaultValue) -> bool;
  static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const std::string& value) -> void;
  static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, int32_t value) -> void;
  static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, double value) -> void;
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
}  // namespace common
