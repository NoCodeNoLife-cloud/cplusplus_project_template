cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 26)

set(MAIN_PROJECT clion_project_template)
project(${MAIN_PROJECT})

include_directories(common)
include_directories(app)
include_directories(ci)

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

add_executable(${MAIN_PROJECT} ${SRC_FILES} ${COMMON_FILES})

find_package(glog CONFIG REQUIRED)
target_link_libraries(${MAIN_PROJECT} PRIVATE glog::glog)

find_package(Boost REQUIRED COMPONENTS system thread url)
target_link_libraries(${MAIN_PROJECT} PRIVATE Boost::system Boost::thread Boost::url)