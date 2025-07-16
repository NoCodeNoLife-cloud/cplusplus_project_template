# CMake version requirement and standard settings
cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Toolchain configuration
if (CMAKE_TOOLCHAIN_FILE)
    message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
else ()
    message(WARNING "No toolchain file specified. Default toolchain will be used.")
endif ()

# Project setup
set(MAIN_PROJECT cpp_project)
project(${MAIN_PROJECT})

# Include directories
include_directories(coco)  # Include directory for coco library
include_directories(app)   # Include directory for application source files
include_directories(proto) # Include directory for protocol buffer files

# Vcpkg dependencies
find_package(Boost REQUIRED COMPONENTS system thread url asio serialization)
find_package(glog CONFIG REQUIRED)
find_package(gtest CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(RapidJSON CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package(directxmath CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)

# Subdirectories
add_subdirectory(ut)     # Add unit test subdirectory
add_subdirectory(app)    # Add application subdirectory
add_subdirectory(coco)   # Add coco library subdirectory
add_subdirectory(proto)  # Add protocol buffer subdirectory