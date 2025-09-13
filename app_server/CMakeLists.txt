# Project
set(SERVER_PROJECT server)

# Source files collection
file(GLOB_RECURSE SRC_FILES
        *.hpp
        *.cc
)

# Define the executable and its source files and framework files
add_executable(${SERVER_PROJECT} ${SRC_FILES} ${FRAMEWORK_FILES})

# Link required libraries
target_link_libraries(${SERVER_PROJECT} PRIVATE
        glog::glog
        yaml-cpp::yaml-cpp
        RapidJSON rapidjson
        OpenSSL::SSL OpenSSL::Crypto
        Microsoft::DirectXMath
        magic_enum::magic_enum
        common_pkg
        common_service
        grpc_service
)
