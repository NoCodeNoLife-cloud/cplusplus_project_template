#pragma once
namespace common {
class IBuffer abstract {
 public:
  virtual ~IBuffer();
  [[nodiscard]] virtual auto capacity() const -> size_t;
  [[nodiscard]] virtual auto position() const -> size_t;
  virtual auto position(size_t newPosition) -> void;
  [[nodiscard]] virtual auto limit() const -> size_t;
  virtual auto limit(size_t newLimit) -> void;
  virtual void clear();
  virtual void flip();
  [[nodiscard]] virtual auto remaining() const -> size_t;
  [[nodiscard]] virtual auto hasRemaining() const -> bool;
  virtual void rewind();

 protected:
  size_t position_{0};
  size_t limit_{0};
  size_t capacity_{0};
};
}  // namespace common
