# Source files collection
file(GLOB_RECURSE SRC_FILES
        *.hpp  # Collect all .hpp files in the app directory
        *.cc  # Collect all .cc files in the app directory
)

# Define the executable and its source files and framework files
add_executable(${MAIN_PROJECT} ${SRC_FILES} ${FRAMEWORK_FILES})

# Add dependencies to ensure that protobuf is generated before building the main project
add_dependencies(${MAIN_PROJECT} generate_proto)

# Link required libraries
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
        magic_enum::magic_enum
        coco
)
