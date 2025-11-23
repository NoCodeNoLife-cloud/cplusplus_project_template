#include "src/rpc/RpcServiceImpl.hpp"

namespace server_app
{
    grpc::Status RpcServiceImpl::RegisterUser(grpc::ServerContext* context,
                                              const rpc::RegisterUserRequest* request,
                                              rpc::AuthResponse* response)
    {
        try
        {
            const bool success = authenticator_.register_user(request->username(), request->password());
            response->set_success(success);
            response->set_message(success ? "User registered successfully" : "Registration failed");
            return grpc::Status::OK;
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
            return {grpc::StatusCode::INTERNAL, e.what()};
        }
    }

    grpc::Status RpcServiceImpl::AuthenticateUser(grpc::ServerContext* context,
                                                  const rpc::AuthenticateUserRequest* request,
                                                  rpc::AuthResponse* response)
    {
        try
        {
            const bool success = authenticator_.authenticate(request->username(), request->password());
            response->set_success(success);
            response->set_message(success ? "Authentication successful" : "Invalid credentials");
            return grpc::Status::OK;
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
            return {grpc::StatusCode::INTERNAL, e.what()};
        }
    }

    grpc::Status RpcServiceImpl::ChangePassword(grpc::ServerContext* context,
                                                const rpc::ChangePasswordRequest* request,
                                                rpc::AuthResponse* response)
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
            return grpc::Status::OK;
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
            return {grpc::StatusCode::INTERNAL, e.what()};
        }
    }

    grpc::Status RpcServiceImpl::ResetPassword(grpc::ServerContext* context,
                                               const rpc::ResetPasswordRequest* request,
                                               rpc::AuthResponse* response)
    {
        try
        {
            const bool success = authenticator_.reset_password(
                request->username(),
                request->new_password()
            );
            response->set_success(success);
            response->set_message(success ? "Password reset successfully" : "Password reset failed");
            return grpc::Status::OK;
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
            return {grpc::StatusCode::INTERNAL, e.what()};
        }
    }

    grpc::Status RpcServiceImpl::DeleteUser(grpc::ServerContext* context,
                                            const rpc::DeleteUserRequest* request,
                                            rpc::AuthResponse* response)
    {
        try
        {
            std::lock_guard<std::mutex> lock(authenticator_.get_users_mutex());
            auto& users = authenticator_.get_users();

            if (!users.contains(request->username()))
            {
                response->set_success(false);
                response->set_message("User not found");
                response->set_error_code(404);
                return grpc::Status::OK;
            }

            users.erase(request->username());
            response->set_success(true);
            response->set_message("User deleted successfully");
            return grpc::Status::OK;
        }
        catch (const std::exception& e)
        {
            response->set_success(false);
            response->set_message("System error: " + std::string(e.what()));
            response->set_error_code(500);
            return {grpc::StatusCode::INTERNAL, e.what()};
        }
    }

    grpc::Status RpcServiceImpl::UserExists(grpc::ServerContext* context,
                                            const rpc::DeleteUserRequest* request,
                                            rpc::AuthResponse* response)
    {
        try
        {
            const bool exists = authenticator_.user_exists(request->username());
            response->set_success(exists);
            response->set_message(exists ? "User exists" : "User not found");
            return grpc::Status::OK;
        }
        catch (const std::exception& e)
        {
            response->set_success(false);
            response->set_message("System error: " + std::string(e.what()));
            response->set_error_code(500);
            return {grpc::StatusCode::INTERNAL, e.what()};
        }
    }

    grpc::Status RpcServiceImpl::HandleAuthException(const common::AuthenticationException& e,
                                                     rpc::AuthResponse* response)
    {
        response->set_success(false);
        response->set_message(e.what());

        // Map exception types to error codes
        if (std::string(e.what()).find("already exists") != std::string::npos)
        {
            response->set_error_code(409); // Conflict
        }
        else if (std::string(e.what()).find("not found") != std::string::npos)
        {
            response->set_error_code(404); // Not found
        }
        else if (std::string(e.what()).find("locked") != std::string::npos)
        {
            response->set_error_code(423); // Locked
        }
        else if (std::string(e.what()).find("Invalid password") != std::string::npos)
        {
            response->set_error_code(401); // Unauthorized
        }
        else
        {
            response->set_error_code(400); // Bad request
        }

        return grpc::Status::OK;
    }
} // namespace server_app
