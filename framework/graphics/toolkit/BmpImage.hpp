#pragma once
#include <cstdint>
#include <fstream>
#include <vector>

namespace framework::graphics::toolkit {
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
} // namespace framework::graphics::toolkit
