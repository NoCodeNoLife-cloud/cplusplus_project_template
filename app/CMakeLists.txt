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
        glog::glog                  # Google Logging Library
        Boost::system               # Boost System Library
        Boost::thread               # Boost Thread Library
        Boost::url                  # Boost URL Library
        Boost::serialization        # Boost Serialization Library
        Boost::asio                 # Boost Asio Library
        yaml-cpp::yaml-cpp          # YAML-CPP Library for parsing YAML files
        RapidJSON rapidjson         # RapidJSON Library for JSON processing
        OpenSSL::SSL OpenSSL::Crypto # OpenSSL Libraries for SSL/TLS and cryptographic functions
        Qt5::Widgets                # Qt Widgets Module for GUI applications
        Microsoft::DirectXMath      # DirectX Math Library for mathematical operations
        coco                      # Custom COCO library (assuming it's a custom dependency)
)
