#pragma once
namespace common {
class Point3D {
 public:
  Point3D();

  Point3D(double xVal, double yVal, double zVal);

  [[nodiscard]] auto getX() const -> double;
  [[nodiscard]] auto getY() const -> double;
  [[nodiscard]] auto getZ() const -> double;

  auto setX(double xVal) -> void;
  auto setY(double yVal) -> void;
  auto setZ(double zVal) -> void;

  [[nodiscard]] auto distanceTo(const Point3D& other) const -> double;

 private:
  double x_;
  double y_;
  double z_;
};
}  // namespace common
