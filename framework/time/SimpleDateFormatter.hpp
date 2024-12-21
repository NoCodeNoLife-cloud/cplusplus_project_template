// Created by author ethereal on 2024/11/30.
// Copyright (c) 2024 ethereal. All rights reserved.
#pragma once
#include <ctime>
#include <string>

namespace framework::util::time {

class SimpleDateFormatter {
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

}  // namespace framework::util::time
