#pragma once
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace common {
/// @brief Interface for JSON serializable objects.
/// This interface defines the contract for objects that can be serialized to
/// and deserialized from JSON format using the RapidJSON library. Any class
/// that implements this interface must provide implementations for the
/// serialize and deserialize methods.
class IJsonSerializable {
 public:
  virtual ~IJsonSerializable() = default;

  /// @brief Serializes the object to JSON.
  virtual auto serialize(rapidjson::Writer<rapidjson::StringBuffer>& writer) const -> void = 0;

  /// @brief Deserializes the object from JSON.
  virtual auto deserialize(const rapidjson::Value& json) -> void = 0;
};
}  // namespace common
