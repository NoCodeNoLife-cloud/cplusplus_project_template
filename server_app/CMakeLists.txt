# Project
set(SERVER_PROJECT server_app)

# Source files collection
file(GLOB_RECURSE SRC_FILES
        *.hpp
        *.cc
)

# Define the executable and its source files and framework files
add_executable(${SERVER_PROJECT} ${SRC_FILES} ${FRAMEWORK_FILES})

# Add dependencies to ensure that protobuf is generated before building the main project
add_dependencies(${SERVER_PROJECT} generate_proto)

# Link required libraries
target_link_libraries(${SERVER_PROJECT} PRIVATE
        glog::glog
        Boost::system
        Boost::thread
        Boost::url
        Boost::serialization
        Boost::asio
        yaml-cpp::yaml-cpp
        RapidJSON rapidjson
        OpenSSL::SSL OpenSSL::Crypto
        Qt5::Widgets
        Microsoft::DirectXMath
        magic_enum::magic_enum
        common_pkg
        common_service
        grpc_service
)
