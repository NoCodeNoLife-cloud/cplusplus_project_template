#include "BmpImage.hpp"

#include <stdexcept>

namespace common {
BmpImage::BmpImage(const int32_t width, const int32_t height) : width_(width), height_(height) {
  if (width <= 0 || height <= 0) {
    throw std::invalid_argument("Invalid image dimensions");
  }
  pixels_.resize(width * height * 3, 0);
}

auto BmpImage::setPixel(const int32_t x, const int32_t y, const uint8_t r, const uint8_t g, const uint8_t b) -> void {
  if (x < 0 || x >= width_ || y < 0 || y >= height_) {
    return;
  }
  const int32_t invertedY = height_ - 1 - y;
  const size_t index = (invertedY * width_ + x) * 3;
  pixels_[index] = b;
  pixels_[index + 1] = g;
  pixels_[index + 2] = r;
}

auto BmpImage::save(const std::string& filename) const -> void {
  const int32_t rowSize = width_ * 3 + 3 & ~3;
  const int32_t pixelDataSize = rowSize * height_;
  const uint64_t fileSize = sizeof(BitMapFileHeader) + sizeof(BitmapInfoHeader) + pixelDataSize;
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
  if (!file) {
    throw std::runtime_error("can't create file: " + filename);
  }
  file.write(reinterpret_cast<const char*>(&fileHeader), sizeof(fileHeader));
  file.write(reinterpret_cast<const char*>(&infoHeader), sizeof(infoHeader));
  constexpr char padding[3] = {};
  for (int32_t y = 0; y < height_; ++y) {
    const int32_t rowStart = y * width_ * 3;
    file.write(reinterpret_cast<const char*>(&pixels_[rowStart]), width_ * 3);
    file.write(padding, rowSize - width_ * 3);
  }
}
}  // namespace common
