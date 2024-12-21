#pragma once
#include <boost/serialization/serialization.hpp>

namespace common::iface
{
    template <typename T>
    class IfaceBoostSerializable abstract
    {
    public:
        virtual ~IfaceBoostSerializable() = default;

    private:
        friend class boost::serialization::access;
        template <class Archive>
        void serialize(Archive& archive, unsigned int version);
    };

    template <typename T>
    template <class Archive>
    void IfaceBoostSerializable<T>::serialize(Archive& archive, const unsigned int version)
    {
        static_cast<T*>(this)->serializeImpl(archive, version);
    }
}
