# Project
set(LOG_SERVICE glog_service)

# Creating a Common Library Target
add_library(${LOG_SERVICE} INTERFACE)

# Set the header file path
target_include_directories(${LOG_SERVICE} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Link required libraries
target_link_libraries(${LOG_SERVICE} INTERFACE
        glog::glog
        Boost::headers
        yaml-cpp::yaml-cpp
)