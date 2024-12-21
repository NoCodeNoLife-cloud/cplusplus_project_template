#pragma once
#include <fstream>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include "io/interface/IfaceJsonSerializable.hpp"

namespace common::io::serialize
{
    template <typename T>concept DerivedFromJsonSerializable = std::is_base_of_v<iface::IfaceJsonSerializable, T>;

    class JsonSerializer abstract
    {
    public:
        JsonSerializer() = delete;

        template <DerivedFromJsonSerializable T>
        static auto saveStudentToJsonFile(const T& entity, const std::string& filename) -> void
        {
            rapidjson::StringBuffer buffer;
            rapidjson::PrettyWriter writer(buffer);
            entity.serialize(writer);
            std::ofstream ofs(filename);
            if (!ofs)
            {
                throw std::runtime_error("Failed to open file for writing: " + filename);
            }
            ofs << buffer.GetString();
            ofs.close();
        }

        template <DerivedFromJsonSerializable T>
        static auto loadStudentFromJsonFile(const std::string& filename) -> T
        {
            T entity{};
            std::ifstream ifs(filename);
            if (!ifs)
            {
                throw std::runtime_error("Failed to open file for reading: " + filename);
            }
            const std::string jsonStr{std::istreambuf_iterator(ifs), std::istreambuf_iterator<char>()};
            ifs.close();
            rapidjson::Document document;
            if (document.Parse(jsonStr.c_str()).HasParseError())
            {
                throw std::runtime_error("JSON parse error!");
            }
            if (document.IsObject())
            {
                entity.deserialize(document);
            }
            return entity;
        }

        static auto getStringOrDefault(const rapidjson::Value& json, const char* key,
                                       const std::string& defaultValue) -> std::string
        {
            if (json.HasMember(key) && json[key].IsString())
            {
                return json[key].GetString();
            }
            return defaultValue;
        }

        static auto getIntOrDefault(const rapidjson::Value& json, const char* key, const int defaultValue) -> int
        {
            if (json.HasMember(key) && json[key].IsInt())
            {
                return json[key].GetInt();
            }
            return defaultValue;
        }

        static auto getDoubleOrDefault(const rapidjson::Value& json, const char* key,
                                       const double defaultValue) -> double
        {
            if (json.HasMember(key) && json[key].IsDouble())
            {
                return json[key].GetDouble();
            }
            return defaultValue;
        }

        static auto getBoolOrDefault(const rapidjson::Value& json, const char* key, const bool defaultValue) -> bool
        {
            if (json.HasMember(key) && json[key].IsBool())
            {
                return json[key].GetBool();
            }
            return defaultValue;
        }

        static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const std::string& value) -> void
        {
            writer.Key(key);
            writer.String(value.c_str());
        }

        static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const int value) -> void
        {
            writer.Key(key);
            writer.Int(value);
        }

        static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const double value) -> void
        {
            writer.Key(key);
            writer.Double(value);
        }

        static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const bool value) -> void
        {
            writer.Key(key);
            writer.Bool(value);
        }
    };
}
