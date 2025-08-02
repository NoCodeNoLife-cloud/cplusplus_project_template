#include "Point3D.hpp"

#include <cmath>

namespace common {
Point3D::Point3D() : x_(0), y_(0), z_(0) {}

Point3D::Point3D(const double xVal, const double yVal, const double zVal) : x_(xVal), y_(yVal), z_(zVal) {}

auto Point3D::getX() const -> double { return x_; }

auto Point3D::getY() const -> double { return y_; }

auto Point3D::getZ() const -> double { return z_; }

auto Point3D::setX(const double xVal) -> void { x_ = xVal; }

auto Point3D::setY(const double yVal) -> void { y_ = yVal; }

auto Point3D::setZ(const double zVal) -> void { z_ = zVal; }

auto Point3D::distanceTo(const Point3D& other) const -> double {
  const double dx = x_ - other.x_;
  const double dy = y_ - other.y_;
  const double dz = z_ - other.z_;
  return std::sqrt(dx * dx + dy * dy + dz * dz);
}
}  // namespace common
