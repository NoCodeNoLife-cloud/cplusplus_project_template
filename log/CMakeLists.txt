# Project
set(LOG_SERVICE common_service)

# Collecting public library source files
file(GLOB_RECURSE SERVICE_FILES
        *.hpp
        *.cc
)

# Creating a Common Library Target
add_library(${LOG_SERVICE} ${SERVICE_FILES})

# Set the header file path
target_include_directories(${LOG_SERVICE} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link required libraries
target_link_libraries(${LOG_SERVICE} PRIVATE
        glog::glog
        ${Boost_INCLUDE_DIRS}
        yaml-cpp::yaml-cpp
)