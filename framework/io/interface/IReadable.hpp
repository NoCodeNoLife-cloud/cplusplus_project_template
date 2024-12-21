#pragma once

namespace framework::iface
{

class IReadable abstract
{
  public:
    virtual ~IReadable() = default;

    virtual auto read() -> int32_t = 0;
};

} // namespace framework::iface
