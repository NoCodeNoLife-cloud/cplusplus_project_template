#include "src/serializer/JsonObjectSerializer.hpp"

#include <string>

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

namespace fox
{
    auto JsonObjectSerializer::getStringOrDefault(const rapidjson::Value& json, const char* key,
                                                  const std::string& defaultValue) noexcept -> std::string
    {
        if (json.HasMember(key) && json[key].IsString())
        {
            return json[key].GetString();
        }
        return defaultValue;
    }

    auto JsonObjectSerializer::getIntOrDefault(const rapidjson::Value& json, const char* key,
                                               const int32_t defaultValue) noexcept -> int32_t
    {
        if (json.HasMember(key) && json[key].IsInt())
        {
            return json[key].GetInt();
        }
        return defaultValue;
    }

    auto JsonObjectSerializer::getDoubleOrDefault(const rapidjson::Value& json, const char* key,
                                                  const double defaultValue) noexcept -> double
    {
        if (json.HasMember(key) && json[key].IsDouble())
        {
            return json[key].GetDouble();
        }
        return defaultValue;
    }

    auto JsonObjectSerializer::getBoolOrDefault(const rapidjson::Value& json, const char* key,
                                                const bool defaultValue) noexcept -> bool
    {
        if (json.HasMember(key) && json[key].IsBool())
        {
            return json[key].GetBool();
        }
        return defaultValue;
    }

    auto JsonObjectSerializer::serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer,
                                              const char* key, const std::string& value) noexcept -> void
    {
        writer.Key(key);
        writer.String(value.c_str());
    }

    auto JsonObjectSerializer::serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer,
                                              const char* key, const int32_t value) noexcept -> void
    {
        writer.Key(key);
        writer.Int(value);
    }

    auto JsonObjectSerializer::serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer,
                                              const char* key, const double value) noexcept -> void
    {
        writer.Key(key);
        writer.Double(value);
    }

    auto JsonObjectSerializer::serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer,
                                              const char* key, const bool value) noexcept -> void
    {
        writer.Key(key);
        writer.Bool(value);
    }
}
