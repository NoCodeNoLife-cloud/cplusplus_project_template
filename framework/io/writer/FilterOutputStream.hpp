#pragma once
#include <io/writer/AbstractOutputStream.hpp>

namespace framework::io::writer {
  class FilterOutputStream : public AbstractOutputStream {
  public:
    explicit FilterOutputStream(std::shared_ptr<AbstractOutputStream> outputStream);
    ~FilterOutputStream() override;
    auto write(std::byte b) -> void override;
    auto write(const std::vector<std::byte>& buffer) -> void override;
    auto write(const std::vector<std::byte>& buffer, size_t offset, size_t len) -> void override;
    auto flush() -> void override;
    auto close() -> void override;

  protected:
    std::shared_ptr<AbstractOutputStream> output_stream_;
  };
} // namespace framework::io::writer
