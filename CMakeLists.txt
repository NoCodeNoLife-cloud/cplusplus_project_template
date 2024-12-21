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
set(MAIN_PROJECT project_template)
project(${MAIN_PROJECT})

#includes
include_directories(framework)
include_directories(client)
include_directories(ci)

#sources
set(SRC_DIR client)
set(SRC_HEADER_DIR client)
file(GLOB_RECURSE SRC_FILES
        ${SRC_HEADER_DIR}/*.hpp
        ${SRC_DIR}/*.cc
)

set(FRAMEWORK_DIR framework)
set(FRAMEWORK_HEADER_DIR framework)
file(GLOB_RECURSE FRAMEWORK_FILES
        ${FRAMEWORK_DIR}/*.hpp
        ${FRAMEWORK_HEADER_DIR}/*.cc
)

#dependencies
find_package(Boost REQUIRED COMPONENTS system thread url)
find_package(glog CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)

#executable
add_executable(${MAIN_PROJECT} ${SRC_FILES} ${FRAMEWORK_FILES})

#link
target_link_libraries(${MAIN_PROJECT} PRIVATE glog::glog)
target_link_libraries(${MAIN_PROJECT} PRIVATE Boost::system)
target_link_libraries(${MAIN_PROJECT} PRIVATE Boost::thread)
target_link_libraries(${MAIN_PROJECT} PRIVATE Boost::url)
target_link_libraries(${MAIN_PROJECT} PRIVATE yaml-cpp::yaml-cpp)

#subdirectory
add_subdirectory(ci)