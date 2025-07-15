#Executable
add_executable(${MAIN_PROJECT} ${SRC_FILES} ${FRAMEWORK_FILES})
Add_dependencies(${MAIN_PROJECT} generate_proto)

#Link
target_link_libraries(${MAIN_PROJECT} PRIVATE
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
        coco
)
