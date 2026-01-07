#include "src/graphics/Point3D.hpp"

#include <iostream>

namespace common
{
    Point2D::Point2D() noexcept = default;

    Point2D::Point2D(const double x, const double y) noexcept
        : x_(x), y_(y)
    {
    }

    auto Point2D::getX() const noexcept -> double
    {
        return x_;
    }

    auto Point2D::getY() const noexcept -> double
    {
        return y_;
    }

    auto Point2D::setX(const double x) noexcept -> void
    {
        x_ = x;
    }

    auto Point2D::setY(const double y) noexcept -> void
    {
        y_ = y;
    }

    auto Point2D::operator+=(const Point2D& other) noexcept -> Point2D&
    {
        x_ += other.x_;
        y_ += other.y_;
        return *this;
    }

    auto Point2D::operator-=(const Point2D& other) noexcept -> Point2D&
    {
        x_ -= other.x_;
        y_ -= other.y_;
        return *this;
    }

    auto Point2D::operator-() const noexcept -> Point2D
    {
        return {-x_, -y_};
    }

    auto operator+(Point2D lhs, const Point2D& rhs) noexcept -> Point2D
    {
        lhs += rhs;
        return lhs;
    }

    auto operator-(Point2D lhs, const Point2D& rhs) noexcept -> Point2D
    {
        lhs -= rhs;
        return lhs;
    }

    auto operator==(const Point2D& lhs, const Point2D& rhs) noexcept -> bool
    {
        return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
    }

    auto operator!=(const Point2D& lhs, const Point2D& rhs) noexcept -> bool
    {
        return !(lhs == rhs);
    }

    auto operator<<(std::ostream& os, const Point2D& point) -> std::ostream&
    {
        os << "(" << point.getX() << ", " << point.getY() << ")";
        return os;
    }
}
