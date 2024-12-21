#include "Point2D.hpp"

namespace common
{
    Point2D::Point2D(): x_(0.0), y_(0.0)
    {
    }

    Point2D::Point2D(const double x, const double y): x_(x), y_(y)
    {
    }

    auto Point2D::getX() const -> double { return x_; }

    auto Point2D::getY() const -> double { return y_; }

    auto Point2D::setX(const double x) -> void { x_ = x; }

    auto Point2D::setY(const double y) -> void { y_ = y; }

    auto Point2D::operator+=(const Point2D& other) -> Point2D&
    {
        x_ += other.x_;
        y_ += other.y_;
        return *this;
    }

    auto Point2D::operator-=(const Point2D& other) -> Point2D&
    {
        x_ -= other.x_;
        y_ -= other.y_;
        return *this;
    }

    auto Point2D::operator-() const -> Point2D
    {
        return {-x_, -y_};
    }
}
