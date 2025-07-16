# Collecting public library source files
file(GLOB_RECURSE COCO_SRCS "*.cc" "*.cpp")  # Collect all .cc and .cpp files recursively
file(GLOB_RECURSE COCO_HEADERS "*.h" "*.hpp")  # Collect all .h and .hpp files recursively

# Creating a Common Library Target
add_library(coco ${COCO_SRCS} ${COCO_HEADERS})  # Create a static library named 'coco' with the collected source and header files

# Set the header file path
target_include_directories(coco PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})  # Make the current source directory available as an include directory for the 'coco' library

# Link required libraries
target_link_libraries(coco PRIVATE
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
)