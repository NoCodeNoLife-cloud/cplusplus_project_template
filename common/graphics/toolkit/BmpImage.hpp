#pragma once
#include <fstream>
#include <vector>
#include <cstdint>
#include <stdexcept>

namespace common::graphics::toolkit
{
#pragma pack(push, 1)
    struct BITMAPFILEHEADER
    {
        uint16_t bfType;
        uint32_t bfSize;
        uint16_t bfReserved1;
        uint16_t bfReserved2;
        uint32_t bfOffBits;
    };

    struct BITMAPINFOHEADER
    {
        uint32_t biSize;
        int32_t biWidth;
        int32_t biHeight;
        uint16_t biPlanes;
        uint16_t biBitCount;
        uint32_t biCompression;
        uint32_t biSizeImage;
        int32_t biXPelsPerMeter;
        int32_t biYPelsPerMeter;
        uint32_t biClrUsed;
        uint32_t biClrImportant;
    };
#pragma pack(pop)
    class BmpImage
    {
    public:
        BmpImage(int32_t width, int32_t height);
        void setPixel(int32_t x, int32_t y, uint8_t r, uint8_t g, uint8_t b);
        void save(const std::string& filename) const;
    private:
        int32_t width_;
        int32_t height_;
        std::vector<uint8_t> pixels_;
    };

    inline BmpImage::BmpImage(int32_t width, int32_t height): width_(width), height_(height)
    {
        if (width <= 0 || height <= 0)
        {
            throw std::invalid_argument("Invalid image dimensions");
        }
        pixels_.resize(width * height * 3, 0);
    }

    inline void BmpImage::setPixel(int32_t x, int32_t y, uint8_t r, uint8_t g, uint8_t b)
    {
        if (x < 0 || x >= width_ || y < 0 || y >= height_)
        {
            return;
        }
        int32_t invertedY = height_ - 1 - y;
        size_t index = (invertedY * width_ + x) * 3;
        pixels_[index] = b;
        pixels_[index + 1] = g;
        pixels_[index + 2] = r;
    }

    inline void BmpImage::save(const std::string& filename) const
    {
        const int rowSize = (width_ * 3 + 3) & ~3;
        const int pixelDataSize = rowSize * height_;
        const unsigned long long fileSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + pixelDataSize;
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
        if (!file)
        {
            throw std::runtime_error("can't create file: " + filename);
        }
        file.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
        file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));
        constexpr char padding[3] = {};
        for (int y = 0; y < height_; ++y)
        {
            const int rowStart = y * width_ * 3;
            file.write(reinterpret_cast<const char*>(&pixels_[rowStart]), width_ * 3);
            file.write(padding, rowSize - width_ * 3);
        }
    }
}
