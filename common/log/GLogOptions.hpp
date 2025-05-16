#pragma once
#include <string>
#include <boost/serialization/access.hpp>
#include <boost/serialization/nvp.hpp>
#include <io/interface/IBoostSerializable.hpp>

namespace common {
  class GLogOptions final : public IBoostSerializable<GLogOptions> {
  public:
    GLogOptions();
    ~GLogOptions() override;
    GLogOptions(const GLogOptions& other);
    GLogOptions& operator=(const GLogOptions& other);
    GLogOptions(GLogOptions&& other) noexcept;
    GLogOptions& operator=(const GLogOptions&& other);
    [[nodiscard]] auto minLogLevel() const -> int32_t;
    [[nodiscard]] auto logName() const -> std::string;

  private:
    friend class boost::serialization::access;
    int32_t min_log_level_{0};
    std::string log_name_{"glog_main"};
    template <class Archive>
    auto serialize(Archive& ar, const unsigned int version) -> void;
  };

  template <class Archive>
  auto GLogOptions::serialize(Archive& ar, const unsigned int version) -> void {
    ar & BOOST_SERIALIZATION_NVP(min_log_level_);
    ar & BOOST_SERIALIZATION_NVP(log_name_);
  }
}
