#pragma once
#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>

namespace fox
{
#pragma pack(push, 1)
    /// @brief BMP file header structure
    /// @details This structure represents the BMP file header which contains
    ///          information about the BMP file format and layout
    struct BitMapFileHeader
    {
        /// @brief BMP file type, should be 'BM'
        uint16_t bf_type_;
        /// @brief Size of the BMP file in bytes
        uint32_t bf_size_;
        /// @brief Reserved field (must be zero)
        uint16_t bf_reserved1_;
        /// @brief Reserved field (must be zero)
        uint16_t bf_reserved2_;
        /// @brief Offset to the start of image data
        uint32_t bf_off_bits_;
    };

    /// @brief BMP info header structure
    /// @details This structure contains information about the dimensions and color format of a BMP image
    struct BitmapInfoHeader
    {
        /// @brief Size of this header (40 bytes)
        uint32_t bi_size_;
        /// @brief Width of the bitmap in pixels
        int32_t bi_width_;
        /// @brief Height of the bitmap in pixels
        int32_t bi_height_;
        /// @brief Number of color planes (must be 1)
        uint16_t bi_planes_;
        /// @brief Number of bits per pixel (1, 4, 8, 16, 24, or 32)
        uint16_t bi_bit_count_;
        /// @brief Compression method used (0 = none, 1 = RLE-8, 2 = RLE-4)
        uint32_t bi_compression_;
        /// @brief Size of the image data in bytes (maybe 0 for uncompressed images)
        uint32_t bi_size_image_;
        /// @brief Horizontal resolution in pixels per meter
        int32_t bi_x_pels_per_meter_;
        /// @brief Vertical resolution in pixels per meter
        int32_t bi_y_pels_per_meter_;
        /// @brief Number of colors in the color palette (0 = default)
        uint32_t bi_clr_used_;
        /// @brief Number of important colors (0 = all are important)
        uint32_t bi_clr_important_;
    };
#pragma pack(pop)

    /// @brief A class for creating and manipulating BMP images
    /// @details This class allows creating BMP images, setting pixel colors, and saving to files
    class BmpImage
    {
    public:
        /// @brief Constructs a BmpImage with specified dimensions
        /// @param width The width of the image in pixels
        /// @param height The height of the image in pixels
        /// @throws std::invalid_argument if width or height is non-positive
        explicit BmpImage(int32_t width, int32_t height);

        /// @brief Constructs a BmpImage by loading from a file
        /// @param filename The name of the file to load the image from
        /// @throws std::runtime_error if the file cannot be loaded or is not a valid BMP
        explicit BmpImage(const std::string& filename);

        /// @brief Sets the color of a pixel at the specified coordinates
        /// @param x The x-coordinate of the pixel
        /// @param y The y-coordinate of the pixel
        /// @param r The red component of the color (0-255)
        /// @param g The green component of the color (0-255)
        /// @param b The blue component of the color (0-255)
        auto setPixel(int32_t x, int32_t y, uint8_t r, uint8_t g, uint8_t b) noexcept -> void;

        /// @brief Gets the color of a pixel at the specified coordinates
        /// @param x The x-coordinate of the pixel
        /// @param y The y-coordinate of the pixel
        /// @param r Reference to store the red component of the color (0-255)
        /// @param g Reference to store the green component of the color (0-255)
        /// @param b Reference to store the blue component of the color (0-255)
        /// @return true if the coordinates are valid, false otherwise
        [[nodiscard]] auto getPixel(int32_t x, int32_t y, uint8_t& r, uint8_t& g, uint8_t& b) const noexcept -> bool;

        /// @brief Saves the BMP image to a file
        /// @param filename The name of the file to save the image to
        /// @throws std::runtime_error if the file cannot be created
        auto save(const std::string& filename) const -> void;

        /// @brief Gets the width of the image
        /// @return The width of the image in pixels
        [[nodiscard]] auto getWidth() const noexcept -> int32_t;

        /// @brief Gets the height of the image
        /// @return The height of the image in pixels
        [[nodiscard]] auto getHeight() const noexcept -> int32_t;

    private:
        int32_t width_{};
        int32_t height_{};
        std::vector<uint8_t> pixels_{};

        /// @brief Loads a BMP image from a file
        /// @param filename The name of the file to load the image from
        /// @throws std::runtime_error if the file cannot be loaded or is not a valid BMP
        auto load(const std::string& filename) -> void;
    };

    inline BmpImage::BmpImage(const int32_t width, const int32_t height) : width_(width),
        height_(height)
    {
        if (width <= 0 || height <= 0)
        {
            throw std::invalid_argument("Invalid image dimensions");
        }
        pixels_.resize(static_cast<size_t>(width) * static_cast<size_t>(height) * 3, 0);
    }

    inline BmpImage::BmpImage(const std::string& filename) : width_(0), height_(0)
    {
        load(filename);
    }

    inline auto BmpImage::setPixel(const int32_t x, const int32_t y, const uint8_t r, const uint8_t g,
                                   const uint8_t b) noexcept -> void
    {
        if (x < 0 || x >= width_ || y < 0 || y >= height_)
        {
            return;
        }
        const int32_t invertedY = height_ - 1 - y;
        const size_t index = static_cast<size_t>(invertedY * width_ + x) * 3;
        pixels_[index] = b;
        pixels_[index + 1] = g;
        pixels_[index + 2] = r;
    }

    inline auto BmpImage::getPixel(const int32_t x, const int32_t y, uint8_t& r, uint8_t& g, uint8_t& b) const noexcept -> bool
    {
        if (x < 0 || x >= width_ || y < 0 || y >= height_)
        {
            return false;
        }
        const int32_t invertedY = height_ - 1 - y;
        const size_t index = static_cast<size_t>(invertedY * width_ + x) * 3;
        b = pixels_[index];
        g = pixels_[index + 1];
        r = pixels_[index + 2];
        return true;
    }

    inline auto BmpImage::save(const std::string& filename) const -> void
    {
        const int32_t rowSize = (width_ * 3 + 3) & ~3;
        const int32_t pixelDataSize = rowSize * height_;
        const uint64_t fileSize = sizeof(BitMapFileHeader) + sizeof(BitmapInfoHeader) + static_cast<uint64_t>(
            pixelDataSize);
        BitMapFileHeader fileHeader{};
        fileHeader.bf_type_ = 0x4D42;
        fileHeader.bf_size_ = fileSize;
        fileHeader.bf_off_bits_ = sizeof(BitMapFileHeader) + sizeof(BitmapInfoHeader);
        BitmapInfoHeader infoHeader{};
        infoHeader.bi_size_ = sizeof(BitmapInfoHeader);
        infoHeader.bi_width_ = width_;
        infoHeader.bi_height_ = height_;
        infoHeader.bi_planes_ = 1;
        infoHeader.bi_bit_count_ = 24;
        infoHeader.bi_compression_ = 0;
        infoHeader.bi_size_image_ = pixelDataSize;
        std::ofstream file(filename, std::ios::binary | std::ios::trunc);
        if (!file)
        {
            throw std::runtime_error("can't create file: " + filename);
        }
        file.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
        file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));
        constexpr char padding[3] = {};
        for (int32_t y = 0; y < height_; ++y)
        {
            const size_t rowStart = static_cast<size_t>(y * width_ * 3);
            file.write(reinterpret_cast<const char*>(&pixels_[rowStart]), width_ * 3);
            file.write(padding, rowSize - width_ * 3);
        }
    }

    inline auto BmpImage::getWidth() const noexcept -> int32_t
    {
        return width_;
    }

    inline auto BmpImage::getHeight() const noexcept -> int32_t
    {
        return height_;
    }

    inline auto BmpImage::load(const std::string& filename) -> void
    {
        std::ifstream file(filename, std::ios::binary);
        if (!file)
        {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        BitMapFileHeader fileHeader;
        BitmapInfoHeader infoHeader;

        file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
        if (file.gcount() != sizeof(fileHeader) || fileHeader.bf_type_ != 0x4D42)  // Check 'BM' signature
        {
            throw std::runtime_error("Invalid BMP file: " + filename);
        }

        file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));
        if (file.gcount() != sizeof(infoHeader) || infoHeader.bi_bit_count_ != 24)  // Only support 24-bit BMP
        {
            throw std::runtime_error("Unsupported BMP format (only 24-bit BMP is supported): " + filename);
        }

        width_ = infoHeader.bi_width_;
        height_ = infoHeader.bi_height_;

        // Resize pixel data
        pixels_.resize(static_cast<size_t>(width_) * static_cast<size_t>(height_) * 3);

        // Calculate row size (must be multiple of 4 bytes)
        const int32_t rowSize = (width_ * 3 + 3) & ~3;
        const size_t padding = static_cast<size_t>(rowSize - width_ * 3);

        // Seek to the beginning of pixel data
        file.seekg(fileHeader.bf_off_bits_);

        // Read pixel data row by row (BMP stores rows bottom-to-top)
        std::vector<char> rowBuffer(static_cast<size_t>(width_ * 3));
        for (int32_t y = height_ - 1; y >= 0; --y)
        {
            file.read(rowBuffer.data(), rowBuffer.size());
            if (file.gcount() != static_cast<std::streamsize>(rowBuffer.size()))
            {
                throw std::runtime_error("Error reading pixel data from file: " + filename);
            }

            const size_t rowIndex = static_cast<size_t>(y * width_ * 3);

            // Copy pixels (BGR to RGB)
            for (int32_t x = 0; x < width_; ++x)
            {
                const size_t srcIndex = static_cast<size_t>(x * 3);
                const size_t dstIndex = rowIndex + srcIndex;
                pixels_[dstIndex]     = static_cast<uint8_t>(rowBuffer[srcIndex + 2]); // R
                pixels_[dstIndex + 1] = static_cast<uint8_t>(rowBuffer[srcIndex + 1]); // G
                pixels_[dstIndex + 2] = static_cast<uint8_t>(rowBuffer[srcIndex]);     // B
            }

            // Skip padding bytes
            if (padding > 0)
            {
                file.ignore(static_cast<std::streamsize>(padding));
            }
        }
    }
}
