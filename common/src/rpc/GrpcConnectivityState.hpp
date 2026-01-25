#pragma once

namespace common::rpc {
    enum class GrpcConnectivityState {
        IDLE,
        CONNECTING,
        READY,
        TRANSIENT_FAILURE,
        SHUTDOWN
    };
}
