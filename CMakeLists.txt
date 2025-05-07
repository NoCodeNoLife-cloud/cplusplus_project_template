#cmake
cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 26)

#toolchain
if (CMAKE_TOOLCHAIN_FILE)
    message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
else ()
    message(WARNING "No toolchain file specified. Default toolchain will be used.")
endif ()

#project
set(MAIN_PROJECT cpp_project)
project(${MAIN_PROJECT})

#includes
include_directories(common)
include_directories(boot)

#sources
set(SRC_DIR boot)
set(SRC_HEADER_DIR boot)
file(GLOB_RECURSE SRC_FILES
        ${SRC_HEADER_DIR}/*.hpp
        ${SRC_DIR}/*.cc
)

set(FRAMEWORK_DIR common)
set(FRAMEWORK_HEADER_DIR common)
file(GLOB_RECURSE FRAMEWORK_FILES
        ${FRAMEWORK_DIR}/*.hpp
        ${FRAMEWORK_HEADER_DIR}/*.cc
)

#vcpkg dependencies
find_package(Boost REQUIRED COMPONENTS system thread url asio)
find_package(glog CONFIG REQUIRED)
find_package(gtest CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(RapidJSON CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

#executable
add_executable(${MAIN_PROJECT} ${SRC_FILES} ${FRAMEWORK_FILES})

#link
target_link_libraries(${MAIN_PROJECT} PRIVATE glog::glog)
target_link_libraries(${MAIN_PROJECT} PRIVATE Boost::system)
target_link_libraries(${MAIN_PROJECT} PRIVATE Boost::thread)
target_link_libraries(${MAIN_PROJECT} PRIVATE Boost::url)
target_link_libraries(${MAIN_PROJECT} PRIVATE Boost::asio)
target_link_libraries(${MAIN_PROJECT} PRIVATE yaml-cpp::yaml-cpp)
target_link_libraries(${MAIN_PROJECT} PRIVATE RapidJSON rapidjson)
target_link_libraries(${MAIN_PROJECT} PRIVATE OpenSSL::SSL OpenSSL::Crypto)

#subdirectory
add_subdirectory(ut)