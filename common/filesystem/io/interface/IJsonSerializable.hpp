#pragma once
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

namespace common {
class IJsonSerializable abstract {
 public:
  virtual ~IJsonSerializable() = default;
  virtual auto serialize(
      rapidjson::Writer<rapidjson::StringBuffer>& writer) const -> void = 0;
  virtual auto deserialize(const rapidjson::Value& json) -> void = 0;
};
}  // namespace common
