#include "src/graphics/Point3D.hpp"

#include <iostream>

namespace common
{
    Point3D::Point3D() noexcept = default;

    Point3D::Point3D(const double x, const double y, const double z) noexcept
        : x_(x), y_(y), z_(z)
    {
    }

    auto Point3D::getX() const noexcept -> double
    {
        return x_;
    }

    auto Point3D::getY() const noexcept -> double
    {
        return y_;
    }

    auto Point3D::getZ() const noexcept -> double
    {
        return z_;
    }

    auto Point3D::setX(const double x) noexcept -> void
    {
        x_ = x;
    }

    auto Point3D::setY(const double y) noexcept -> void
    {
        y_ = y;
    }

    auto Point3D::setZ(const double z) noexcept -> void
    {
        z_ = z;
    }

    auto Point3D::operator+=(const Point3D& other) noexcept -> Point3D&
    {
        x_ += other.x_;
        y_ += other.y_;
        z_ += other.z_;
        return *this;
    }

    auto Point3D::operator-=(const Point3D& other) noexcept -> Point3D&
    {
        x_ -= other.x_;
        y_ -= other.y_;
        z_ -= other.z_;
        return *this;
    }

    auto Point3D::operator-() const noexcept -> Point3D
    {
        return {-x_, -y_, -z_};
    }

    auto operator+(Point3D lhs, const Point3D& rhs) noexcept -> Point3D
    {
        lhs += rhs;
        return lhs;
    }

    auto operator-(Point3D lhs, const Point3D& rhs) noexcept -> Point3D
    {
        lhs -= rhs;
        return lhs;
    }

    auto operator==(const Point3D& lhs, const Point3D& rhs) noexcept -> bool
    {
        return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY() && lhs.getZ() == rhs.getZ();
    }

    auto operator!=(const Point3D& lhs, const Point3D& rhs) noexcept -> bool
    {
        return !(lhs == rhs);
    }

    auto operator<<(std::ostream& os, const Point3D& point) -> std::ostream&
    {
        os << "(" << point.getX() << ", " << point.getY() << ", " << point.getZ() << ")";
        return os;
    }
}
