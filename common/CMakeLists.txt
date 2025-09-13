# Project
set(COMMON_FRAMEWORK common_pkg)

# Creating a Common Library Target
add_library(${COMMON_FRAMEWORK} INTERFACE)

# Set the header file path
target_include_directories(${COMMON_FRAMEWORK} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Link required libraries
target_link_libraries(${COMMON_FRAMEWORK} INTERFACE
        glog::glog
        Boost::headers
        yaml-cpp::yaml-cpp
        RapidJSON rapidjson
        OpenSSL::SSL OpenSSL::Crypto
        magic_enum::magic_enum
        Microsoft::DirectXMath
)