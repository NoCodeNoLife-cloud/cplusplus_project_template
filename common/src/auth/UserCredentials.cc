#include "UserCredentials.hpp"

#include <utility>

namespace common
{
    UserCredentials::UserCredentials(std::string username, std::string hashed_password, std::string salt)
        : username_(std::move(username)),
          hashed_password_(std::move(hashed_password)),
          salt_(std::move(salt)),
          failed_attempts_(0),
          last_failed_attempt_(std::chrono::system_clock::time_point::min())
    {
    }

    const std::string& UserCredentials::get_username() const
    {
        return username_;
    }

    const std::string& UserCredentials::get_hashed_password() const
    {
        return hashed_password_;
    }

    const std::string& UserCredentials::get_salt() const
    {
        return salt_;
    }

    size_t UserCredentials::get_failed_attempts() const
    {
        return failed_attempts_;
    }

    void UserCredentials::increment_failed_attempts()
    {
        failed_attempts_++;
        last_failed_attempt_ = std::chrono::system_clock::now();
    }

    void UserCredentials::reset_failed_attempts()
    {
        failed_attempts_ = 0;
        last_failed_attempt_ = std::chrono::system_clock::time_point::min();
    }

    bool UserCredentials::is_locked() const
    {
        const auto now = std::chrono::system_clock::now();
        const auto minutes_since_last_fail = std::chrono::duration_cast<std::chrono::minutes>(
            now - last_failed_attempt_).count();

        // Account locked after 5 failed attempts within 5 minutes
        return failed_attempts_ >= 5 && minutes_since_last_fail < 5;
    }
} // common
