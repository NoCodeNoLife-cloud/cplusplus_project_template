#include "src/rpc/RpcServiceImpl.hpp"
#include <unordered_map>
#include <string_view>

namespace server_app
{
    RpcServiceImpl::RpcServiceImpl(const std::string& db_path) noexcept
        : authenticator_(db_path)
    {
    }

    auto RpcServiceImpl::RegisterUser(::grpc::ServerContext* /*context*/,
                                      const ::rpc::RegisterUserRequest* const request,
                                      ::rpc::AuthResponse* const response)
        -> ::grpc::Status
    {
        try
        {
            const bool success = authenticator_.register_user(request->username(), request->password());
            response->set_success(success);
            response->set_message(success ? "User registered successfully" : "Registration failed");
            return ::grpc::Status::OK;
        }
        catch (const common::AuthenticationException& e)
        {
            return HandleAuthException(e, response);
        }
        catch (const std::exception& e)
        {
            response->set_success(false);
            response->set_message("System error: " + std::string(e.what()));
            response->set_error_code(500);
            return {::grpc::StatusCode::INTERNAL, e.what()};
        }
    }

    auto RpcServiceImpl::AuthenticateUser(::grpc::ServerContext* /*context*/,
                                          const ::rpc::AuthenticateUserRequest* const request,
                                          ::rpc::AuthResponse* const response)
        -> ::grpc::Status
    {
        try
        {
            const bool success = authenticator_.authenticate(request->username(), request->password());
            response->set_success(success);
            response->set_message(success ? "Authentication successful" : "Invalid credentials");
            return ::grpc::Status::OK;
        }
        catch (const common::AuthenticationException& e)
        {
            return HandleAuthException(e, response);
        }
        catch (const std::exception& e)
        {
            response->set_success(false);
            response->set_message("System error: " + std::string(e.what()));
            response->set_error_code(500);
            return {::grpc::StatusCode::INTERNAL, e.what()};
        }
    }

    auto RpcServiceImpl::ChangePassword(::grpc::ServerContext* /*context*/,
                                        const ::rpc::ChangePasswordRequest* const request,
                                        ::rpc::AuthResponse* const response)
        -> ::grpc::Status
    {
        try
        {
            const bool success = authenticator_.change_password(
                request->username(),
                request->current_password(),
                request->new_password()
            );
            response->set_success(success);
            response->set_message(success ? "Password changed successfully" : "Password change failed");
            return ::grpc::Status::OK;
        }
        catch (const common::AuthenticationException& e)
        {
            return HandleAuthException(e, response);
        }
        catch (const std::exception& e)
        {
            response->set_success(false);
            response->set_message("System error: " + std::string(e.what()));
            response->set_error_code(500);
            return {::grpc::StatusCode::INTERNAL, e.what()};
        }
    }

    auto RpcServiceImpl::ResetPassword(::grpc::ServerContext* /*context*/,
                                       const ::rpc::ResetPasswordRequest* const request,
                                       ::rpc::AuthResponse* const response)
        -> ::grpc::Status
    {
        try
        {
            const bool success = authenticator_.reset_password(
                request->username(),
                request->new_password()
            );
            response->set_success(success);
            response->set_message(success ? "Password reset successfully" : "Password reset failed");
            return ::grpc::Status::OK;
        }
        catch (const common::AuthenticationException& e)
        {
            return HandleAuthException(e, response);
        }
        catch (const std::exception& e)
        {
            response->set_success(false);
            response->set_message("System error: " + std::string(e.what()));
            response->set_error_code(500);
            return {::grpc::StatusCode::INTERNAL, e.what()};
        }
    }

    auto RpcServiceImpl::DeleteUser(::grpc::ServerContext* /*context*/,
                                    const ::rpc::DeleteUserRequest* const request,
                                    ::rpc::AuthResponse* const response)
        -> ::grpc::Status
    {
        try
        {
            const bool success = authenticator_.delete_user(request->username());
            response->set_success(success);
            if (success)
            {
                response->set_message("User deleted successfully");
            }
            else
            {
                response->set_message("User deletion failed");
            }
            return ::grpc::Status::OK;
        }
        catch (const std::exception& e)
        {
            response->set_success(false);
            response->set_message("System error: " + std::string(e.what()));
            response->set_error_code(500);
            return {::grpc::StatusCode::INTERNAL, e.what()};
        }
    }

    auto RpcServiceImpl::UserExists(::grpc::ServerContext* /*context*/,
                                    const ::rpc::UserExistsRequest* const request,
                                    ::rpc::AuthResponse* const response)
        -> ::grpc::Status
    {
        try
        {
            const bool exists = authenticator_.user_exists(request->username());
            response->set_success(exists);
            response->set_message(exists ? "User exists" : "User not found");
            return ::grpc::Status::OK;
        }
        catch (const std::exception& e)
        {
            response->set_success(false);
            response->set_message("System error: " + std::string(e.what()));
            response->set_error_code(500);
            return {::grpc::StatusCode::INTERNAL, e.what()};
        }
    }

    auto RpcServiceImpl::HandleAuthException(const common::AuthenticationException& e,
                                             ::rpc::AuthResponse* const response) noexcept
        -> ::grpc::Status
    {
        response->set_success(false);
        response->set_message(e.what());

        // Map exception types to error codes using table-driven approach
        static const std::unordered_map<std::string_view, int> error_map = {
            {"already exists", 409}, // Conflict
            {"not found", 404}, // Not found
            {"locked", 423}, // Locked
            {"Invalid password", 401} // Unauthorized
        };

        const std::string error_msg = e.what();
        response->set_error_code(400); // Default error code (Bad request)

        for (const auto& [pattern, code] : error_map)
        {
            if (error_msg.find(pattern) != std::string::npos)
            {
                response->set_error_code(code);
                break;
            }
        }

        return ::grpc::Status::OK;
    }
} // namespace server_app
