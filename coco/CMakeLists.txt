# Framework files collection
file(GLOB_RECURSE FRAMEWORK_FILES
        *.hpp  # Collect all .hpp files in the framework directory
        *.cc # Collect all .cc files in the framework directory
)

# Collecting public library source files
file(GLOB_RECURSE COCO_SRCS "*.cc" "*.cpp")  # Collect all .cc and .cpp files recursively
file(GLOB_RECURSE COCO_HEADERS "*.h" "*.hpp")  # Collect all .h and .hpp files recursively

# Creating a Common Library Target
add_library(coco ${COCO_SRCS} ${COCO_HEADERS})  # Create a static library named 'coco' with the collected source and header files

# Set the header file path
target_include_directories(coco PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})  # Make the current source directory available as an include directory for the 'coco' library

# Link required libraries
target_link_libraries(coco PRIVATE
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
        Microsoft::DirectXMath
)