#pragma once
#include <string>
#include <boost/multiprecision/cpp_dec_float.hpp>

namespace framework {
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
}
