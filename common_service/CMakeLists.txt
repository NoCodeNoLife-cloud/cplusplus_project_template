# Project
set(COMMON_SERVICE common_service)

# Collecting public library source files
file(GLOB_RECURSE SERVICE_FILES
        *.hpp
        *.cc
)

# Creating a Common Library Target
add_library(${COMMON_SERVICE} ${SERVICE_FILES})

# Set the header file path
target_include_directories(${COMMON_SERVICE} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link required libraries
target_link_libraries(${COMMON_SERVICE} PRIVATE
        glog::glog
        ${Boost_INCLUDE_DIRS}
        yaml-cpp::yaml-cpp
        RapidJSON rapidjson
        OpenSSL::SSL OpenSSL::Crypto
        Qt5::Widgets
        Microsoft::DirectXMath
)