#pragma once
#include "../../filesystem/File.hpp"
#include "../interface/IAppendable.hpp"
#include "FilterOutputStream.hpp"

namespace framework::io::writer {
  class PrintStream final : public FilterOutputStream, public iface::IAppendable<PrintStream> {
  public:
    PrintStream(std::shared_ptr<AbstractOutputStream> outStream, bool autoFlush, const std::locale& loc);

    auto append(char c) -> PrintStream& override;

    auto append(const std::string& str) -> PrintStream& override;

    auto append(const std::string& str, size_t start, size_t end) -> PrintStream& override;

    auto print(bool b) const -> void;

    auto print(char c) const -> void;

    auto print(int32_t i) const -> void;

    auto print(int64_t l) const -> void;

    auto print(float f) const -> void;

    auto print(double d) const -> void;

    auto print(const char* s) const -> void;

    auto print(const std::string& s) const -> void;

    auto print(const std::vector<char>& v) const -> void;

    auto println(bool b) const -> void;

    auto println(char c) const -> void;

    auto println(int32_t i) const -> void;

    auto println(int64_t l) const -> void;

    auto println(float f) const -> void;

    auto println(double d) const -> void;

    auto println(const char* s) const -> void;

    auto println(const std::string& s) const -> void;

    auto println(const std::vector<char>& v) const -> void;

    auto flush() -> void override;

    auto close() -> void override;

  protected:
    bool auto_flush_{false};
    bool error_state_{false};
    std::locale locale_;

    auto flushIfNeeded() const -> void;
  };
} // namespace framework::io::writer
