#pragma once
#include "AbstractWriter.hpp"

namespace common {
class CharArrayWriter final : public AbstractWriter,
                              IAppendable<CharArrayWriter> {
 public:
  CharArrayWriter();
  explicit CharArrayWriter(int32_t initialSize);
  ~CharArrayWriter() override;
  void write(char c) override;
  auto write(const std::vector<char>& cBuf, size_t off, size_t len)
      -> void override;
  void write(const std::string& str, size_t off, size_t len) override;
  auto writeTo(AbstractWriter& out) const -> void;
  CharArrayWriter& append(const std::string& csq) override;
  CharArrayWriter& append(const std::string& csq, size_t start,
                          size_t end) override;
  CharArrayWriter& append(char c) override;
  auto reset() -> void;
  [[nodiscard]] auto toCharArray() const -> std::vector<char>;
  [[nodiscard]] auto size() const -> size_t;
  [[nodiscard]] auto toString() const -> std::string override;
  auto flush() -> void override;
  auto close() -> void override;

 private:
  std::vector<char> buf_;
  size_t count_{0};
};
}  // namespace common
