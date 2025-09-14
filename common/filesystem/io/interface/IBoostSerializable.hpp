#pragma once
#include <cstdint>

namespace boost::serialization
{
class access;
}

namespace fox
{
/// @brief Interface for Boost serialization
/// This interface provides a common base for objects that can be serialized using Boost.Serialization.
/// Classes implementing this interface need to provide a serializeImpl method for the actual serialization logic.
/// @tparam T The type to be serialized (the derived class)
template <typename T> class IBoostSerializable
{
  public:
    /// @brief Virtual destructor for proper cleanup of derived classes
    virtual ~IBoostSerializable();

  private:
    /// @brief Friend declaration to allow Boost serialization access
    friend class boost::serialization::access;

    /// @brief Serialization implementation
    /// This method is called by the Boost serialization library to serialize the object.
    /// It forwards the call to the derived class's serializeImpl method.
    /// @tparam Archive The type of archive used for serialization
    /// @param archive Archive object used for serialization
    /// @param version Version number for serialization
    template <class Archive> auto serialize(Archive &archive, uint32_t version) -> void;
};

template <typename T> IBoostSerializable<T>::~IBoostSerializable() = default;

template <typename T>
template <class Archive>
auto IBoostSerializable<T>::serialize(Archive &archive, const uint32_t version) -> void
{
    static_cast<T *>(this)->serializeImpl(archive, version);
}
} // namespace fox
