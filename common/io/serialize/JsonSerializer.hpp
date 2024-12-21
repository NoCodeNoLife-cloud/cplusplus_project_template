#pragma once
#include <fstream>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/stringbuffer.h>
#include "io/interface/IJsonSerializable.hpp"

namespace common::io::serialize
{
    template <typename T>concept DerivedFromJsonSerializable = std::is_base_of_v<iface::IJsonSerializable, T>;

    class JsonSerializer abstract
    {
    public:
        JsonSerializer() = delete;
        template <DerivedFromJsonSerializable T> static auto saveStudentToJsonFile(const T& entity, const std::string& filename) -> void;
        template <DerivedFromJsonSerializable T> static auto loadStudentFromJsonFile(const std::string& filename) -> T;
        static auto getStringOrDefault(const rapidjson::Value& json, const char* key, const std::string& defaultValue) -> std::string;
        static auto getIntOrDefault(const rapidjson::Value& json, const char* key, int defaultValue) -> int;
        static auto getDoubleOrDefault(const rapidjson::Value& json, const char* key, double defaultValue) -> double;
        static auto getBoolOrDefault(const rapidjson::Value& json, const char* key, bool defaultValue) -> bool;
        static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const std::string& value) -> void;
        static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, int value) -> void;
        static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, double value) -> void;
        static auto serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, bool value) -> void;
    };

    template <DerivedFromJsonSerializable T> auto JsonSerializer::saveStudentToJsonFile(const T& entity, const std::string& filename) -> void
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

    template <DerivedFromJsonSerializable T> auto JsonSerializer::loadStudentFromJsonFile(const std::string& filename) -> T
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

    inline auto JsonSerializer::getStringOrDefault(const rapidjson::Value& json, const char* key, const std::string& defaultValue) -> std::string
    {
        if (json.HasMember(key) && json[key].IsString())
        {
            return json[key].GetString();
        }
        return defaultValue;
    }

    inline auto JsonSerializer::getIntOrDefault(const rapidjson::Value& json, const char* key, const int defaultValue) -> int
    {
        if (json.HasMember(key) && json[key].IsInt())
        {
            return json[key].GetInt();
        }
        return defaultValue;
    }

    inline auto JsonSerializer::getDoubleOrDefault(const rapidjson::Value& json, const char* key, const double defaultValue) -> double
    {
        if (json.HasMember(key) && json[key].IsDouble())
        {
            return json[key].GetDouble();
        }
        return defaultValue;
    }

    inline auto JsonSerializer::getBoolOrDefault(const rapidjson::Value& json, const char* key, const bool defaultValue) -> bool
    {
        if (json.HasMember(key) && json[key].IsBool())
        {
            return json[key].GetBool();
        }
        return defaultValue;
    }

    inline auto JsonSerializer::serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const std::string& value) -> void
    {
        writer.Key(key);
        writer.String(value.c_str());
    }

    inline auto JsonSerializer::serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const int value) -> void
    {
        writer.Key(key);
        writer.Int(value);
    }

    inline auto JsonSerializer::serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const double value) -> void
    {
        writer.Key(key);
        writer.Double(value);
    }

    inline auto JsonSerializer::serializeField(rapidjson::Writer<rapidjson::StringBuffer>& writer, const char* key, const bool value) -> void
    {
        writer.Key(key);
        writer.Bool(value);
    }
}
