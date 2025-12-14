#include "UserAuthenticator.hpp"

#include "CryptoUtils.hpp"
#include "src/exception/AuthenticationException.hpp"
#include <sstream>

namespace common
{
    UserAuthenticator::UserAuthenticator(const std::string& db_path,
                                       const PasswordPolicy& policy)
        : password_policy_(policy)
        , password_sql_(db_path)
    {
    }

    bool UserAuthenticator::register_user(const std::string& username,
                                          const std::string& password)
    {
        std::lock_guard lock(users_mutex_);

        // Validate username format
        if (!validate_username(username))
        {
            throw AuthenticationException("Invalid username format. Use alphanumeric characters, underscores, or hyphens (3-20 characters).");
        }

        // Check if username already exists
        if (users_.contains(username) || password_sql_.UserExists(username))
        {
            throw AuthenticationException("Username already exists");
        }

        // Validate password against policy
        if (!password_policy_.validate(password))
        {
            throw AuthenticationException("Password does not meet security requirements");
        }

        // Generate salt and hash password
        auto salt = CryptoUtils::generate_salt();
        auto hashed_password = CryptoUtils::hash_password(password, salt);

        // Store user credentials in database
        std::ostringstream credential_stream;
        credential_stream << salt << ":" << hashed_password;
        if (!password_sql_.RegisterUser(username, credential_stream.str()))
        {
            throw AuthenticationException("Failed to register user in database");
        }

        // Store user credentials in memory cache
        users_[username] = std::make_unique<UserCredentials>(username, hashed_password, salt);
        return true;
    }

    bool UserAuthenticator::authenticate(const std::string& username,
                                         const std::string& password)
    {
        std::lock_guard lock(users_mutex_);

        // Try to get user from memory cache first
        auto it = users_.find(username);
        if (it == users_.end())
        {
            // If not in cache, try to load from database
            auto user_opt = load_user_from_db(username);
            if (user_opt.has_value())
            {
                // Add to cache
                users_[username] = std::make_unique<UserCredentials>(user_opt.value());
                it = users_.find(username);
            }
        }

        if (it == users_.end())
        {
            throw AuthenticationException("User not found");
        }

        const auto& user = it->second;

        // Check if account is locked
        if (user->is_locked())
        {
            throw AuthenticationException("Account is locked due to too many failed attempts. Please try again later.");
        }

        // Verify password
        if (const auto hashed_input = CryptoUtils::hash_password(password, user->get_salt()); CryptoUtils::secure_compare(hashed_input, user->get_hashed_password()))
        {
            user->reset_failed_attempts();
            return true;
        }
        else
        {
            user->increment_failed_attempts();
            throw AuthenticationException("Invalid password");
        }
    }

    bool UserAuthenticator::change_password(const std::string& username,
                                            const std::string& current_password,
                                            const std::string& new_password)
    {
        // First verify current password
        if (!authenticate(username, current_password))
        {
            throw AuthenticationException("Current password is incorrect");
        }

        std::lock_guard lock(users_mutex_);
        const auto it = users_.find(username);
        if (it == users_.end())
        {
            throw AuthenticationException("User not found");
        }

        // Validate new password
        if (!password_policy_.validate(new_password))
        {
            throw AuthenticationException("New password does not meet security requirements");
        }

        // Generate new salt and hash
        auto salt = CryptoUtils::generate_salt();
        auto hashed_password = CryptoUtils::hash_password(new_password, salt);

        // Update credentials in database
        std::ostringstream credential_stream;
        credential_stream << salt << ":" << hashed_password;
        if (!password_sql_.ResetPassword(username, credential_stream.str()))
        {
            throw AuthenticationException("Failed to update password in database");
        }

        // Update credentials in memory cache
        auto new_credentials = std::make_unique<UserCredentials>(username, hashed_password, salt);
        it->second = std::move(new_credentials);
        return true;
    }

    bool UserAuthenticator::reset_password(const std::string& username,
                                           const std::string& new_password)
    {
        std::lock_guard lock(users_mutex_);

        // Validate new password
        if (!password_policy_.validate(new_password))
        {
            throw AuthenticationException("New password does not meet security requirements");
        }

        // Generate new credentials
        auto salt = CryptoUtils::generate_salt();
        auto hashed_password = CryptoUtils::hash_password(new_password, salt);

        // Update credentials in database
        std::ostringstream credential_stream;
        credential_stream << salt << ":" << hashed_password;
        if (!password_sql_.ResetPassword(username, credential_stream.str()))
        {
            throw AuthenticationException("Failed to reset password in database");
        }

        // Update credentials in memory cache or add if not exists
        auto new_credentials = std::make_unique<UserCredentials>(username, hashed_password, salt);
        users_[username] = std::move(new_credentials);
        return true;
    }

    bool UserAuthenticator::delete_user(const std::string& username)
    {
        std::lock_guard lock(users_mutex_);

        // Delete from database
        if (!password_sql_.DeleteUser(username))
        {
            return false;
        }

        // Delete from memory cache
        users_.erase(username);
        return true;
    }

    bool UserAuthenticator::user_exists(const std::string& username) const
    {
        std::lock_guard lock(users_mutex_);
        // Check in memory cache first
        if (users_.contains(username))
        {
            return true;
        }
        // Check in database
        return password_sql_.UserExists(username);
    }

    void UserAuthenticator::set_password_policy(const PasswordPolicy& policy)
    {
        password_policy_ = policy;
    }

    bool UserAuthenticator::validate_username(const std::string& username)
    {
        // Allow letters, numbers, underscores, hyphens; 3-20 characters
        const std::regex username_pattern("^[a-zA-Z0-9_-]{3,20}$");
        return std::regex_match(username, username_pattern);
    }

    auto UserAuthenticator::load_user_from_db(const std::string& username) const
        -> std::optional<UserCredentials>
    {
        if (!password_sql_.UserExists(username))
        {
            return std::nullopt;
        }

        const std::string credentials_data = password_sql_.GetUser(username);
        if (credentials_data.empty())
        {
            return std::nullopt;
        }

        // Parse credentials data (salt:hashed_password)
        const size_t delimiter_pos = credentials_data.find(':');
        if (delimiter_pos == std::string::npos)
        {
            return std::nullopt;
        }

        const std::string salt = credentials_data.substr(0, delimiter_pos);
        const std::string hashed_password = credentials_data.substr(delimiter_pos + 1);

        return UserCredentials(username, hashed_password, salt);
    }

    auto UserAuthenticator::get_users()
        -> std::unordered_map<std::string, std::unique_ptr<UserCredentials>>&
    {
        return users_;
    }

    auto UserAuthenticator::get_users_mutex() const
        -> std::mutex&
    {
        return users_mutex_;
    }
} // common
