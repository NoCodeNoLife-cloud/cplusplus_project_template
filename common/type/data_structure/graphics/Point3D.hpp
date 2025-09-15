#pragma once
#include <cmath>

namespace fox
{
    /// @brief A class representing a point in 3D space.
    /// The Point3D class provides basic functionality for working with points in three-dimensional space,
    /// including setting and getting coordinates, and calculating distances between points.
    class Point3D
    {
    public:
        Point3D() : x_(0), y_(0), z_(0)
        {
        }

        Point3D(const double xVal, const double yVal, const double zVal) : x_(xVal), y_(yVal), z_(zVal)
        {
        }

        /// @brief Get the X coordinate
        /// @return X coordinate value
        [[nodiscard]] auto getX() const -> double
        {
            return x_;
        }

        /// @brief Get the Y coordinate
        /// @return Y coordinate value
        [[nodiscard]] auto getY() const -> double
        {
            return y_;
        }

        /// @brief Get the Z coordinate
        /// @return Z coordinate value
        [[nodiscard]] auto getZ() const -> double
        {
            return z_;
        }

        /// @brief Set the X coordinate
        /// @param xVal New X coordinate value
        auto setX(const double xVal) -> void
        {
            x_ = xVal;
        }

        /// @brief Set the Y coordinate
        /// @param yVal New Y coordinate value
        auto setY(const double yVal) -> void
        {
            y_ = yVal;
        }

        /// @brief Set the Z coordinate
        /// @param zVal New Z coordinate value
        auto setZ(const double zVal) -> void
        {
            z_ = zVal;
        }

        /// @brief Calculate distance to another point
        /// @param other The other point to calculate distance to
        /// @return Distance to the other point
        [[nodiscard]] auto distanceTo(const Point3D& other) const -> double
        {
            const double dx = x_ - other.x_;
            const double dy = y_ - other.y_;
            const double dz = z_ - other.z_;
            return std::sqrt(dx * dx + dy * dy + dz * dz);
        }

    private:
        double x_;
        double y_;
        double z_;
    };
} // namespace fox
