# Project
set(LOG_SERVICE glog_service)

file(GLOB_RECURSE GLOG_SRC_FILES
        src/*.cc
)

# Creating a Common Library Target
add_library(${LOG_SERVICE} ${GLOG_SRC_FILES})

# Set the header file path
target_include_directories(${LOG_SERVICE} PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link required libraries
target_link_libraries(${LOG_SERVICE} PUBLIC
        glog::glog
        yaml-cpp::yaml-cpp
        fmt::fmt
)