#pragma once
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <string>

namespace framework::entity::base_type {

class BigDecimal {
 public:
  explicit BigDecimal(const std::string& str);

  explicit BigDecimal(double num);

  auto operator+(const BigDecimal& other) const -> BigDecimal;

  auto operator-(const BigDecimal& other) const -> BigDecimal;

  auto operator*(const BigDecimal& other) const -> BigDecimal;

  auto operator/(const BigDecimal& other) const -> BigDecimal;

  auto operator==(const BigDecimal& other) const -> bool;

  auto operator!=(const BigDecimal& other) const -> bool;

  auto operator<(const BigDecimal& other) const -> bool;

  auto operator>(const BigDecimal& other) const -> bool;

  [[nodiscard]] auto toString() const -> std::string;

 private:
  boost::multiprecision::cpp_dec_float_100 value_;
};

}  // namespace framework::entity::base_type
