#pragma once
namespace fox {
/// @brief A class representing a point in 3D space.
/// The Point3D class provides basic functionality for working with points in three-dimensional space,
/// including setting and getting coordinates, and calculating distances between points.
class Point3D {
 public:
  Point3D();

  Point3D(double xVal, double yVal, double zVal);

  /// @brief Get the X coordinate
  /// @return X coordinate value
  [[nodiscard]] auto getX() const -> double;

  /// @brief Get the Y coordinate
  /// @return Y coordinate value
  [[nodiscard]] auto getY() const -> double;

  /// @brief Get the Z coordinate
  /// @return Z coordinate value
  [[nodiscard]] auto getZ() const -> double;

  /// @brief Set the X coordinate
  /// @param xVal New X coordinate value
  auto setX(double xVal) -> void;

  /// @brief Set the Y coordinate
  /// @param yVal New Y coordinate value
  auto setY(double yVal) -> void;

  /// @brief Set the Z coordinate
  /// @param zVal New Z coordinate value
  auto setZ(double zVal) -> void;

  /// @brief Calculate distance to another point
  /// @param other The other point to calculate distance to
  /// @return Distance to the other point
  [[nodiscard]] auto distanceTo(const Point3D& other) const -> double;

 private:
  double x_;
  double y_;
  double z_;
};
}  // namespace fox
