# Project
set(COMMON_PROJECT common_pkg)

# Collecting public library source files
file(GLOB_RECURSE COMMON_FILES
        *.hpp
        *.cc
)

# Creating a Common Library Target
add_library(${COMMON_PROJECT} ${COMMON_FILES})

# Set the header file path
target_include_directories(${COMMON_PROJECT} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link required libraries
target_link_libraries(${COMMON_PROJECT} PRIVATE
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
        magic_enum::magic_enum
        Microsoft::DirectXMath
)