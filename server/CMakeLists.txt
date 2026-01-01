# Project
set(SERVER_PROJECT server)

# Source files collection
file(GLOB_RECURSE SERVER_SRC_FILES
        *.hpp
        *.cc
)

# Define the executable and its source files and framework files
add_executable(${SERVER_PROJECT} ${SERVER_SRC_FILES} ${FRAMEWORK_FILES})

# Link required libraries
target_link_libraries(${SERVER_PROJECT} PRIVATE
        glog::glog
        yaml-cpp::yaml-cpp
        RapidJSON rapidjson
        OpenSSL::SSL OpenSSL::Crypto
        Microsoft::DirectXMath
        magic_enum::magic_enum
        common_pkg
        glog_service
        grpc_service
        fmt::fmt
)
