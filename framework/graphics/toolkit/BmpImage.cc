#include "BmpImage.hpp"
#include <stdexcept>

namespace framework::graphics::toolkit {
    BmpImage::BmpImage(const int32_t width, const int32_t height) : width_(width), height_(height) {
        if (width <= 0 || height <= 0) { throw std::invalid_argument("Invalid image dimensions"); }
        pixels_.resize(width * height * 3, 0);
    }

    void BmpImage::setPixel(const int32_t x, const int32_t y, const uint8_t r, const uint8_t g, const uint8_t b) {
        if (x < 0 || x >= width_ || y < 0 || y >= height_) { return; }
        const int32_t invertedY = height_ - 1 - y;
        const size_t index = (invertedY * width_ + x) * 3;
        pixels_[index] = b;
        pixels_[index + 1] = g;
        pixels_[index + 2] = r;
    }

    void BmpImage::save(const std::string& filename) const {
        const int32_t rowSize = (width_ * 3 + 3) & ~3;
        const int32_t pixelDataSize = rowSize * height_;
        const uint64_t fileSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + pixelDataSize;
        BITMAPFILEHEADER fileHeader{};
        fileHeader.bfType = 0x4D42;
        fileHeader.bfSize = fileSize;
        fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
        BITMAPINFOHEADER infoHeader{};
        infoHeader.biSize = sizeof(BITMAPINFOHEADER);
        infoHeader.biWidth = width_;
        infoHeader.biHeight = height_;
        infoHeader.biPlanes = 1;
        infoHeader.biBitCount = 24;
        infoHeader.biCompression = 0;
        infoHeader.biSizeImage = pixelDataSize;
        std::ofstream file(filename, std::ios::binary | std::ios::trunc);
        if (!file) { throw std::runtime_error("can't create file: " + filename); }
        file.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
        file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));
        constexpr char padding[3] = {};
        for (int32_t y = 0; y < height_; ++y)
        {
            const int32_t rowStart = y * width_ * 3;
            file.write(reinterpret_cast<const char*>(&pixels_[rowStart]), width_ * 3);
            file.write(padding, rowSize - width_ * 3);
        }
    }
} // namespace framework::graphics::toolkit
