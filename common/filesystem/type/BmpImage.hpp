#pragma once
#include <cstdint>
#include <fstream>
#include <vector>

namespace fox {
#pragma pack(push, 1)
/// @brief BMP file header structure
/// @details This structure represents the BMP file header which contains
///          information about the BMP file format and layout
struct BitMapFileHeader {
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
struct BitmapInfoHeader {
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
  /// @brief Size of the image data in bytes (may be 0 for uncompressed images)
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
class BmpImage {
 public:
  BmpImage(int32_t width, int32_t height);

  /// @brief Sets the color of a pixel at the specified coordinates
  /// @param x The x-coordinate of the pixel
  /// @param y The y-coordinate of the pixel
  /// @param r The red component of the color (0-255)
  /// @param g The green component of the color (0-255)
  /// @param b The blue component of the color (0-255)
  auto setPixel(int32_t x, int32_t y, uint8_t r, uint8_t g, uint8_t b) -> void;

  /// @brief Saves the BMP image to a file
  /// @param filename The name of the file to save the image to
  auto save(const std::string& filename) const -> void;

 private:
  int32_t width_;
  int32_t height_;
  std::vector<uint8_t> pixels_;
};
}  // namespace fox
