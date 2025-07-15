#Collecting public library source files
file(GLOB_RECURSE COCO_SRCS "*.cc" "*.cpp")
file(GLOB_RECURSE COCO_HEADERS "*.h" "*.hpp")

#Creating a Common Library Target
add_library(coco ${COCO_SRCS} ${COCO_HEADERS})

#Set the header file path
target_include_directories(coco PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#Link
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
