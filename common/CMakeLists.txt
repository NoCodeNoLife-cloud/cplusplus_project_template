# Project
set(COMMON_FRAMEWORK common_pkg)

file(GLOB_RECURSE FOX_SRC_FILES
        src/*.cc
)

# Creating a Common Library Target
add_library(${COMMON_FRAMEWORK} ${FOX_SRC_FILES})

# Set the header file path
target_include_directories(${COMMON_FRAMEWORK} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link required libraries
target_link_libraries(${COMMON_FRAMEWORK} PUBLIC
        glog::glog
        Boost::headers
        yaml-cpp::yaml-cpp
        RapidJSON rapidjson
        OpenSSL::SSL OpenSSL::Crypto
        magic_enum::magic_enum
        Microsoft::DirectXMath
)