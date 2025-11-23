#pragma once
#include <memory>
#include <grpcpp/grpcpp.h>

#include "generated/RpcService.grpc.pb.h"

namespace client_app
{
    /// @brief RPC client for communicating with the server.
    /// @details This class provides methods to interact with the RPC service.
    class RpcClient
    {
    public:
        explicit RpcClient(const std::shared_ptr<grpc::Channel>& channel);

        [[nodiscard]] auto RegisterUser(const std::string& username,
                                        const std::string& password) const
            -> rpc::AuthResponse;

        [[nodiscard]] auto AuthenticateUser(const std::string& username,
                                            const std::string& password) const
            -> rpc::AuthResponse;

        [[nodiscard]] auto ChangePassword(const std::string& username,
                                          const std::string& current_password,
                                          const std::string& new_password) const
            -> rpc::AuthResponse;

        [[nodiscard]] auto ResetPassword(const std::string& username,
                                         const std::string& new_password) const
            -> rpc::AuthResponse;

        auto ResetPassword(const std::string& username,
                           const std::string& new_password)
            -> rpc::AuthResponse;

        [[nodiscard]] auto DeleteUser(const std::string& username) const
            -> rpc::AuthResponse;

        [[nodiscard]] auto UserExists(const std::string& username) const
            -> rpc::AuthResponse;

    private:
        std::unique_ptr<rpc::RpcService::Stub> stub_{};
    };
} // namespace client_app
