#include "UserAuthenticator.hpp"

#include "CryptoUtils.hpp"
#include "src/exception/AuthenticationException.hpp"

namespace common
{
    UserAuthenticator::UserAuthenticator(const PasswordPolicy& policy)
        : password_policy_(policy)
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
        if (users_.contains(username))
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

        // Store user credentials
        users_[username] = std::make_unique<UserCredentials>(username, hashed_password, salt);
        return true;
    }

    bool UserAuthenticator::authenticate(const std::string& username,
                                         const std::string& password)
    {
        std::lock_guard lock(users_mutex_);

        const auto it = users_.find(username);
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
        // ReSharper disable once CppDFAConstantConditions
        if (!authenticate(username, current_password))
        {
            // ReSharper disable once CppDFAUnreachableCode
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

        // Update credentials
        auto new_credentials = std::make_unique<UserCredentials>(username, hashed_password, salt);
        it->second = std::move(new_credentials);
        return true;
    }

    bool UserAuthenticator::reset_password(const std::string& username,
                                           const std::string& new_password)
    {
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

        // Generate new credentials
        auto salt = CryptoUtils::generate_salt();
        auto hashed_password = CryptoUtils::hash_password(new_password, salt);

        // Replace existing credentials
        it->second = std::make_unique<UserCredentials>(username, hashed_password, salt);
        return true;
    }

    bool UserAuthenticator::user_exists(const std::string& username) const
    {
        std::lock_guard lock(users_mutex_);
        return users_.contains(username);
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
