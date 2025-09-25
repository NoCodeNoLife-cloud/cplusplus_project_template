#pragma once
#include <iostream>

namespace fox
{
    /// @brief A 2D point class
    /// @details This class represents a point in 2D space with x and y coordinates.
    ///          It provides basic operations such as addition, subtraction, and comparison.
    class Point2D
    {
    public:
        Point2D() noexcept;

        Point2D(double x, double y) noexcept;

        /// @brief Get the X coordinate
        /// @return X coordinate value
        [[nodiscard]] auto getX() const noexcept -> double;

        /// @brief Get the Y coordinate
        /// @return Y coordinate value
        [[nodiscard]] auto getY() const noexcept -> double;

        /// @brief Set the X coordinate
        /// @param x X coordinate value
        auto setX(double x) noexcept -> void;

        /// @brief Set the Y coordinate
        /// @param y Y coordinate value
        auto setY(double y) noexcept -> void;

        /// @brief Add another Point2D to this point
        /// @param other Point2D to add
        /// @return Reference to this point
        auto operator+=(const Point2D& other) noexcept -> Point2D&;

        /// @brief Subtract another Point2D from this point
        /// @param other Point2D to subtract
        /// @return Reference to this point
        auto operator-=(const Point2D& other) noexcept -> Point2D&;

        /// @brief Negate this point
        /// @return Negated point
        [[nodiscard]] auto operator-() const noexcept -> Point2D;

        // Friend operators
        friend auto operator+(Point2D lhs, const Point2D& rhs) noexcept -> Point2D;

        friend auto operator-(Point2D lhs, const Point2D& rhs) noexcept -> Point2D;

        friend auto operator==(const Point2D& lhs, const Point2D& rhs) noexcept -> bool;

        friend auto operator!=(const Point2D& lhs, const Point2D& rhs) noexcept -> bool;

        friend auto operator<<(std::ostream& os, const Point2D& point) -> std::ostream&;

    private:
        double x_{0.0};
        double y_{0.0};
    };

    inline Point2D::Point2D() noexcept = default;

    inline Point2D::Point2D(const double x, const double y) noexcept : x_(x), y_(y)
    {
    }

    inline auto Point2D::getX() const noexcept -> double
    {
        return x_;
    }

    inline auto Point2D::getY() const noexcept -> double
    {
        return y_;
    }

    inline auto Point2D::setX(const double x) noexcept -> void
    {
        x_ = x;
    }

    inline auto Point2D::setY(const double y) noexcept -> void
    {
        y_ = y;
    }

    inline auto Point2D::operator+=(const Point2D& other) noexcept -> Point2D&
    {
        x_ += other.x_;
        y_ += other.y_;
        return *this;
    }

    inline auto Point2D::operator-=(const Point2D& other) noexcept -> Point2D&
    {
        x_ -= other.x_;
        y_ -= other.y_;
        return *this;
    }

    inline auto Point2D::operator-() const noexcept -> Point2D
    {
        return {-x_, -y_};
    }

    inline auto operator+(Point2D lhs, const Point2D& rhs) noexcept -> Point2D
    {
        lhs += rhs;
        return lhs;
    }

    inline auto operator-(Point2D lhs, const Point2D& rhs) noexcept -> Point2D
    {
        lhs -= rhs;
        return lhs;
    }

    inline auto operator==(const Point2D& lhs, const Point2D& rhs) noexcept -> bool
    {
        return lhs.getX() == rhs.getX() && lhs.getY() == rhs.getY();
    }

    inline auto operator!=(const Point2D& lhs, const Point2D& rhs) noexcept -> bool
    {
        return !(lhs == rhs);
    }

    inline auto operator<<(std::ostream& os, const Point2D& point) -> std::ostream&
    {
        os << "(" << point.getX() << ", " << point.getY() << ")";
        return os;
    }
}
