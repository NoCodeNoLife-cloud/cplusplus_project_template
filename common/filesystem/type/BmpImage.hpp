#pragma once
#include <cstdint>
#include <fstream>
#include <vector>

namespace common {
#pragma pack(push, 1)
struct BitMapFileHeader {
  uint16_t bf_type_;
  uint32_t bf_size_;
  uint16_t bf_reserved1_;
  uint16_t bf_reserved2_;
  uint32_t bf_off_bits_;
};

struct BitmapInfoHeader {
  uint32_t bi_size_;
  int32_t bi_width_;
  int32_t bi_height_;
  uint16_t bi_planes_;
  uint16_t bi_bit_count_;
  uint32_t bi_compression_;
  uint32_t bi_size_image_;
  int32_t bi_x_pels_per_meter_;
  int32_t bi_y_pels_per_meter_;
  uint32_t bi_clr_used_;
  uint32_t bi_clr_important_;
};
#pragma pack(pop)
class BmpImage {
 public:
  BmpImage(int32_t width, int32_t height);
  auto setPixel(int32_t x, int32_t y, uint8_t r, uint8_t g, uint8_t b) -> void;
  auto save(const std::string& filename) const -> void;

 private:
  int32_t width_;
  int32_t height_;
  std::vector<uint8_t> pixels_;
};
}  // namespace common
