#pragma once
#include <iostream>

namespace common {
class Point2D {
 public:
  Point2D();
  Point2D(double x, double y);

  /// @brief Get the X coordinate
  /// @return X coordinate value
  [[nodiscard]] auto getX() const -> double;

  /// @brief Get the Y coordinate
  /// @return Y coordinate value
  [[nodiscard]] auto getY() const -> double;

  /// @brief Set the X coordinate
  /// @param x X coordinate value
  auto setX(double x) -> void;

  /// @brief Set the Y coordinate
  /// @param y Y coordinate value
  auto setY(double y) -> void;

  /// @brief Add another Point2D to this point
  /// @param other Point2D to add
  /// @return Reference to this point
  auto operator+=(const Point2D& other) -> Point2D&;

  /// @brief Subtract another Point2D from this point
  /// @param other Point2D to subtract
  /// @return Reference to this point
  auto operator-=(const Point2D& other) -> Point2D&;

  /// @brief Negate this point
  /// @return Negated point
  auto operator-() const -> Point2D;

 private:
  double x_;
  double y_;
};

inline Point2D operator+(Point2D lhs, const Point2D& rhs) {
  lhs += rhs;
  return lhs;
}

inline Point2D operator-(Point2D lhs, const Point2D& rhs) {
  lhs -= rhs;
  return lhs;
}

inline bool operator==(const Point2D& lhs, const Point2D& rhs) { return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY(); }

inline bool operator!=(const Point2D& lhs, const Point2D& rhs) { return !(lhs == rhs); }

inline std::ostream& operator<<(std::ostream& os, const Point2D& point) {
  os << "(" << point.getX() << ", " << point.getY() << ")";
  return os;
}
}  // namespace common
