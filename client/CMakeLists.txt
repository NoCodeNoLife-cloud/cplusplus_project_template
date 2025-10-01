# Project
set(CLIENT_PROJECT client)

# Source files collection
file(GLOB_RECURSE CLIENT_SRC_FILES
        *.hpp
        *.cc
)

# Define the executable and its source files and framework files
add_executable(${CLIENT_PROJECT} ${CLIENT_SRC_FILES} ${FRAMEWORK_FILES})

# Link required libraries
target_link_libraries(${CLIENT_PROJECT} PRIVATE
        glog::glog
        yaml-cpp::yaml-cpp
        RapidJSON rapidjson
        OpenSSL::SSL OpenSSL::Crypto
        Microsoft::DirectXMath
        magic_enum::magic_enum
        ${COMMON_FRAMEWORK}
        glog_service
        grpc_service
)
