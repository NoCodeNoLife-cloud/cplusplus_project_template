#pragma once
#include <iostream>

namespace common {
class Point2D {
 public:
  Point2D();
  Point2D(double x, double y);

  [[nodiscard]] auto getX() const -> double;
  [[nodiscard]] auto getY() const -> double;

  auto setX(double x) -> void;
  auto setY(double y) -> void;

  auto operator+=(const Point2D& other) -> Point2D&;
  auto operator-=(const Point2D& other) -> Point2D&;
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

inline bool operator==(const Point2D& lhs, const Point2D& rhs) {
  return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
}

inline bool operator!=(const Point2D& lhs, const Point2D& rhs) {
  return !(lhs == rhs);
}

inline std::ostream& operator<<(std::ostream& os, const Point2D& point) {
  os << "(" << point.getX() << ", " << point.getY() << ")";
  return os;
}
}  // namespace common
