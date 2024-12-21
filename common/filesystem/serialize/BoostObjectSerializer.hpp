#pragma once
#include <filesystem>
#include <fstream>
#include <sstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include "filesystem/io/interface/IBoostSerializable.hpp"

namespace common
{
    template <typename T>
    concept DerivedFromBoostSerializable = std::is_base_of_v<IBoostSerializable<T>, T>;

    class BoostObjectSerializer abstract
    {
    public:
        template <DerivedFromBoostSerializable T>
        static auto serializeObjectToBinaryString(const T& obj) -> std::string;
        template <DerivedFromBoostSerializable T>
            requires std::default_initializable<T>
        static auto deserializeObjectFromBinaryString(const std::string& data) -> T;
        template <DerivedFromBoostSerializable T>
        static auto serializeObjectToXMLFile(const T& obj, const std::filesystem::path& filePath) -> bool;
        template <DerivedFromBoostSerializable T>
        static auto serializeObjectFromXMLFile(const std::filesystem::path& filePath) -> T;
    };

    template <DerivedFromBoostSerializable T>
    auto BoostObjectSerializer::serializeObjectToBinaryString(const T& obj) -> std::string
    {
        std::ostringstream o_string_stream;
        boost::archive::binary_oarchive binary_o_archive(o_string_stream);
        binary_o_archive << obj;
        return o_string_stream.str();
    }

    template <DerivedFromBoostSerializable T>
        requires std::default_initializable<T>
    auto BoostObjectSerializer::deserializeObjectFromBinaryString(const std::string& data) -> T
    {
        T t = T();
        std::istringstream i_string_stream(data);
        boost::archive::binary_iarchive binary_i_archive(i_string_stream);
        binary_i_archive >> t;
        return t;
    }

    template <DerivedFromBoostSerializable T>
    auto BoostObjectSerializer::serializeObjectToXMLFile(const T& obj, const std::filesystem::path& filePath) -> bool
    {
        try
        {
            std::ofstream ofs(filePath);
            boost::archive::xml_oarchive oa(ofs);
            oa << BOOST_SERIALIZATION_NVP(obj);
            return true;
        }
        catch (std::exception& e)
        {
            throw std::runtime_error(e.what());
        }
    }

    template <DerivedFromBoostSerializable T>
    auto BoostObjectSerializer::serializeObjectFromXMLFile(const std::filesystem::path& filePath) -> T
    {
        try
        {
            T t;
            std::ifstream ifs(filePath);
            boost::archive::xml_iarchive ia(ifs);
            ia >> BOOST_SERIALIZATION_NVP(t);
            return t;
        }
        catch (std::exception& e)
        {
            throw std::runtime_error(e.what());
        }
    }
}
