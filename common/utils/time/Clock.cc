#include "Clock.hpp"

#include <format>

namespace fox {
auto Clock::getCurrentDateTimeString() -> std::string {
  const auto now = std::chrono::system_clock::now();
  const auto local_time = std::chrono::current_zone()->to_local(now);
  const auto date = floor<std::chrono::days>(local_time);
  const std::chrono::year_month_day ymd{date};
  const std::chrono::hh_mm_ss time_part{local_time - date};
  return std::format("{0:04d}-{1:02d}-{2:02d} {3:02d}:{4:02d}:{5:02d}", static_cast<int>(ymd.year()), static_cast<unsigned>(ymd.month()), static_cast<unsigned>(ymd.day()), time_part.hours().count(), time_part.minutes().count(), time_part.seconds().count());
}

auto Clock::getCompressedCurrentDateTimeString() -> std::string {
  const auto now = std::chrono::system_clock::now();
  const auto local_time = std::chrono::current_zone()->to_local(now);
  const auto date = floor<std::chrono::days>(local_time);
  const std::chrono::year_month_day ymd{date};
  const std::chrono::hh_mm_ss time_part{local_time - date};
  return std::format("{0:04d}{1:02d}{2:02d}_{3:02d}{4:02d}{5:02d}", static_cast<int>(ymd.year()), static_cast<unsigned>(ymd.month()), static_cast<unsigned>(ymd.day()), time_part.hours().count(), time_part.minutes().count(), time_part.seconds().count());
}
}  // namespace fox
