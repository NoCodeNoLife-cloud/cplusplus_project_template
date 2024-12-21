#pragma once
#include "AbstractOutputStream.hpp"
#include "PipedInputStream.hpp"

namespace framework::io {
    class PipedInputStream;

    class PipedOutputStream final : public AbstractOutputStream
    {
    public:
        explicit PipedOutputStream(const std::shared_ptr<PipedInputStream>& snk);

        ~PipedOutputStream() override;

        auto close() -> void override;

        auto flush() -> void override;

        auto write(std::byte b) -> void override;

        void write(const std::vector<std::byte>& buffer, size_t offset, size_t len) override;

    protected:
        std::shared_ptr<PipedInputStream> snk_;
        bool closed_{true};
        bool connected_{false};
    };
} // namespace framework::io
