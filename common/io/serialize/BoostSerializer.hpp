#pragma once
#include <sstream>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include "io/interface/IfaceBoostSerializable.hpp"

namespace common::io::serialize
{
    template <typename T>concept DerivedFromBoostSerializable = std::is_base_of_v<iface::IfaceBoostSerializable<T>, T>;

    class BoostSerializer abstract
    {
    public:
        template <DerivedFromBoostSerializable T>
        static auto serializeObject(const T& obj) -> std::string;
        template <DerivedFromBoostSerializable T>
        static auto deserializeObject(const std::string& data) -> T;
    };

    template <DerivedFromBoostSerializable T>
    auto BoostSerializer::serializeObject(const T& obj) -> std::string
    {
        std::ostringstream ostringstream;
        boost::archive::binary_oarchive binaryOarchive(ostringstream);
        binaryOarchive << obj;
        return ostringstream.str();
    }

    template <DerivedFromBoostSerializable T>
    auto BoostSerializer::deserializeObject(const std::string& data) -> T
    {
        T t = T();
        std::istringstream istringstream(data);
        boost::archive::binary_iarchive binaryIarchive(istringstream);
        binaryIarchive >> t;
        return t;
    }
}
