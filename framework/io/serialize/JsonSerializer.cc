#include "JsonSerializer.hpp"

namespace framework::io::serialize {

auto JsonSerializer::getStringOrDefault(const rapidjson::Value& json, const char* key, const std::string& defaultValue) -> std::string {
  if (json.HasMember(key) && json[key].IsString()) {
    return json[key].GetString();
  }
  return defaultValue;
}

auto JsonSerializer::getIntOrDefault(const rapidjson::Value& json, const char* key, const int32_t defaultValue) -> int32_t {
  if (json.HasMember(key) && json[key].IsInt()) {
    return json[key].GetInt();
  }
  return defaultValue;
}

auto JsonSerializer::getDoubleOrDefault(const rapidjson::Value& json, const char* key, const double defaultValue) -> double {
  if (json.HasMember(key) && json[key].IsDouble()) {
    return json[key].GetDouble();
  }
  return defaultValue;
}

auto JsonSerializer::getBoolOrDefault(const rapidjson::Value& json, const char* key, const bool defaultValue) -> bool {
  if (json.HasMember(key) && json[key].IsBool()) {
    return json[key].GetBool();
  }
  return defaultValue;
}

auto JsonSerializer::serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const std::string& value) -> void {
  writer.Key(key);
  writer.String(value.c_str());
}

auto JsonSerializer::serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const int32_t value) -> void {
  writer.Key(key);
  writer.Int(value);
}

auto JsonSerializer::serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const double value) -> void {
  writer.Key(key);
  writer.Double(value);
}

auto JsonSerializer::serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const bool value) -> void {
  writer.Key(key);
  writer.Bool(value);
}

}  // namespace framework::io::serialize
