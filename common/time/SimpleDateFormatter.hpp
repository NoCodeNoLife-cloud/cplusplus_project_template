// Created by author ethereal on 2024/11/30.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

namespace common::util::time
{
    class SimpleDateFormatter
    {
    public:
        explicit SimpleDateFormatter(const std::string& pattern);
        auto applyPattern(const std::string& newPattern) -> void;
        [[nodiscard]] auto toPattern() const -> std::string;
        [[nodiscard]] auto format(const std::tm& date) const -> std::string;
        [[nodiscard]] auto parse(const std::string& dateStr) const -> std::tm;
        [[nodiscard]] auto equals(const SimpleDateFormatter& other) const -> bool;
        [[nodiscard]] auto hashCode() const -> size_t;
    private:
        std::string pattern;
        static auto validatePattern(const std::string& pat) -> void;
    };

    inline SimpleDateFormatter::SimpleDateFormatter(const std::string& pattern)
    {
        validatePattern(pattern);
        this->pattern = pattern;
    }

    inline auto SimpleDateFormatter::applyPattern(const std::string& newPattern) -> void
    {
        validatePattern(newPattern);
        this->pattern = newPattern;
    }

    inline auto SimpleDateFormatter::toPattern() const -> std::string
    {
        return this->pattern;
    }

    inline auto SimpleDateFormatter::format(const std::tm& date) const -> std::string
    {
        std::ostringstream oss;
        try
        {
            oss << std::put_time(&date, pattern.c_str());
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Error formatting date: " + std::string(e.what()));
        }
        return oss.str();
    }

    inline auto SimpleDateFormatter::parse(const std::string& dateStr) const -> std::tm
    {
        std::istringstream iss(dateStr);
        std::tm date = {};
        try
        {
            iss >> std::get_time(&date, pattern.c_str());
            if (iss.fail())
            {
                throw std::runtime_error("Failed to parse date: " + dateStr);
            }
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Error parsing date: " + std::string(e.what()));
        }
        return date;
    }

    inline auto SimpleDateFormatter::equals(const SimpleDateFormatter& other) const -> bool
    {
        return this->pattern == other.pattern;
    }

    inline auto SimpleDateFormatter::hashCode() const -> size_t
    {
        return std::hash<std::string>{}(this->pattern);
    }

    inline auto SimpleDateFormatter::validatePattern(const std::string& pat) -> void
    {
        if (pat.empty())
        {
            throw std::invalid_argument("Pattern cannot be empty.");
        }
    }
}
