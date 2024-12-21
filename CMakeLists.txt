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
set(MAIN_PROJECT clion_project_template)
project(${MAIN_PROJECT})

#includes
include_directories(common)
include_directories(app)
include_directories(ci)

#sources
set(SRC_DIR ./app)
set(SRC_HEADER_DIR ./app)
file(GLOB_RECURSE SRC_FILES
        ${SRC_HEADER_DIR}/*.hpp
        ${SRC_DIR}/*.cpp
)

set(COMMON_SRC_DIR ./common)
set(COMMON_SRC_HEADER_DIR ./common)
file(GLOB_RECURSE COMMON_FILES
        ${COMMON_SRC_DIR}/*.hpp
        ${COMMON_SRC_HEADER_DIR}/*.cpp
)

#dependencies
find_package(Boost REQUIRED COMPONENTS system thread url)
find_package(glog CONFIG REQUIRED)

#executable
add_executable(${MAIN_PROJECT} ${SRC_FILES} ${COMMON_FILES})

#link
target_link_libraries(${MAIN_PROJECT} PRIVATE glog::glog Boost::system Boost::thread Boost::url)