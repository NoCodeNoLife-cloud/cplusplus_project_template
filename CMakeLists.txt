#cmake
cmake_minimum_required(VERSION 3.30)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#toolchain
if (CMAKE_TOOLCHAIN_FILE)
    message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")
else ()
    message(WARNING "No toolchain file specified. Default toolchain will be used.")
endif ()

#project
set(MAIN_PROJECT cpp_project)
project(${MAIN_PROJECT})

#includes
include_directories(coco)
include_directories(app)

#sources
set(SRC_DIR app)
set(SRC_HEADER_DIR app)
file(GLOB_RECURSE SRC_FILES
        ${SRC_HEADER_DIR}/*.hpp
        ${SRC_DIR}/*.cc
)

set(FRAMEWORK_DIR coco)
set(FRAMEWORK_HEADER_DIR coco)
file(GLOB_RECURSE FRAMEWORK_FILES
        ${FRAMEWORK_DIR}/*.hpp
        ${FRAMEWORK_HEADER_DIR}/*.cc
)

#vcpkg dependencies
find_package(Boost REQUIRED COMPONENTS system thread url asio serialization)
find_package(glog CONFIG REQUIRED)
find_package(gtest CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(RapidJSON CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Widgets)
find_package(directxmath CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

#protobuf
set(PROTO_SOURCE_DIR "${PROJECT_SOURCE_DIR}/proto" CACHE PATH "Root directory for .proto files")
set(PROTO_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated/proto" CACHE PATH "Output directory for generated code")
file(GLOB_RECURSE PROTO_FILES "${PROTO_SOURCE_DIR}/*.proto")

set(PROTO_SRCS "")
set(PROTO_HDRS "")

find_program(gRPC_CPP_PLUGIN_EXECUTABLE
        NAMES grpc_cpp_plugin
        PATHS
        "$ENV{VCPKG_ROOT}/installed/x64-windows/tools/grpc"
        "$ENV{ProgramFiles}/gRPC/bin"
        "/usr/local/bin"
        DOC "Path to gRPC C++ plugin (new name: grpc_cpp_plugin)"
)

if (NOT gRPC_CPP_PLUGIN_EXECUTABLE)
    message(FATAL_ERROR "Could not find gRPC C++ plugin (grpc_cpp_plugin). "
            "Please verify vcpkg installation or try reinstalling gRPC.")
endif ()

message(STATUS "gRPC C++ plugin found at: ${gRPC_CPP_PLUGIN_EXECUTABLE}")

foreach (proto_file IN LISTS PROTO_FILES)
    get_filename_component(proto_name_we ${proto_file} NAME_WE)
    get_filename_component(proto_rel_path ${proto_file} PATH)
    file(RELATIVE_PATH proto_sub_dir ${PROTO_SOURCE_DIR} ${proto_rel_path})

    set(pb_cc "${PROTO_OUTPUT_DIR}/${proto_sub_dir}/${proto_name_we}.pb.cc")
    set(pb_h "${PROTO_OUTPUT_DIR}/${proto_sub_dir}/${proto_name_we}.pb.h")
    set(grpc_pb_cc "${PROTO_OUTPUT_DIR}/${proto_sub_dir}/${proto_name_we}.grpc.pb.cc")
    set(grpc_pb_h "${PROTO_OUTPUT_DIR}/${proto_sub_dir}/${proto_name_we}.grpc.pb.h")

    file(MAKE_DIRECTORY "${PROTO_OUTPUT_DIR}/${proto_sub_dir}")

    add_custom_command(
            OUTPUT ${pb_cc} ${pb_h} ${grpc_pb_cc} ${grpc_pb_h}
            COMMAND ${Protobuf_PROTOC_EXECUTABLE}
            ARGS
            --cpp_out=${PROTO_OUTPUT_DIR}
            --grpc_out=${PROTO_OUTPUT_DIR}
            --plugin=protoc-gen-grpc=${gRPC_CPP_PLUGIN_EXECUTABLE}
            -I${PROTO_SOURCE_DIR}
            ${proto_file}
            DEPENDS ${proto_file}
            COMMENT "Generating gRPC code for ${proto_file}"
    )

    list(APPEND PROTO_SRCS ${pb_cc} ${grpc_pb_cc})
    list(APPEND PROTO_HDRS ${pb_h} ${grpc_pb_h})
endforeach ()

add_custom_target(generate_proto ALL DEPENDS ${PROTO_SRCS} ${PROTO_HDRS})

#executable
add_executable(${MAIN_PROJECT} ${SRC_FILES} ${FRAMEWORK_FILES})
add_dependencies(${MAIN_PROJECT} generate_proto)

#link
target_link_libraries(${MAIN_PROJECT} PRIVATE glog::glog)
target_link_libraries(${MAIN_PROJECT} PRIVATE Boost::system)
target_link_libraries(${MAIN_PROJECT} PRIVATE Boost::thread)
target_link_libraries(${MAIN_PROJECT} PRIVATE Boost::url)
target_link_libraries(${MAIN_PROJECT} PRIVATE Boost::serialization)
target_link_libraries(${MAIN_PROJECT} PRIVATE Boost::asio)
target_link_libraries(${MAIN_PROJECT} PRIVATE yaml-cpp::yaml-cpp)
target_link_libraries(${MAIN_PROJECT} PRIVATE RapidJSON rapidjson)
target_link_libraries(${MAIN_PROJECT} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(${MAIN_PROJECT} PRIVATE Qt5::Widgets)
target_link_libraries(${MAIN_PROJECT} PRIVATE Microsoft::DirectXMath)
target_link_libraries(${MAIN_PROJECT} PRIVATE gRPC::grpc++ gRPC::grpc++_reflection protobuf::libprotobuf)

#subdirectory
add_subdirectory(ut)