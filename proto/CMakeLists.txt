# Protobuf configuration
set(PROTO_SOURCE_DIR "${PROJECT_SOURCE_DIR}/proto" CACHE PATH "Root directory for .proto files")
set(PROTO_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated/proto" CACHE PATH "Output directory for generated code")
file(GLOB_RECURSE PROTO_FILES "${PROTO_SOURCE_DIR}/*.proto")  # Collect all .proto files recursively

set(PROTO_SRCS "")  # Initialize list to store generated source files
set(PROTO_HDRS "")  # Initialize list to store generated header files

# Find the gRPC C++ plugin
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

# Generate gRPC code for each .proto file
foreach (proto_file IN LISTS PROTO_FILES)
    get_filename_component(proto_name_we ${proto_file} NAME_WE)  # Get the filename without extension
    get_filename_component(proto_rel_path ${proto_file} PATH)  # Get the relative path of the proto file
    file(RELATIVE_PATH proto_sub_dir ${PROTO_SOURCE_DIR} ${proto_rel_path})  # Get the subdirectory path

    set(pb_cc "${PROTO_OUTPUT_DIR}/${proto_sub_dir}/${proto_name_we}.pb.cc")  # Path for generated .pb.cc file
    set(pb_h "${PROTO_OUTPUT_DIR}/${proto_sub_dir}/${proto_name_we}.pb.h")  # Path for generated .pb.h file
    set(grpc_pb_cc "${PROTO_OUTPUT_DIR}/${proto_sub_dir}/${proto_name_we}.grpc.pb.cc")  # Path for generated .grpc.pb.cc file
    set(grpc_pb_h "${PROTO_OUTPUT_DIR}/${proto_sub_dir}/${proto_name_we}.grpc.pb.h")  # Path for generated .grpc.pb.h file

    file(MAKE_DIRECTORY "${PROTO_OUTPUT_DIR}/${proto_sub_dir}")  # Create the output directory if it doesn't exist

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

    list(APPEND PROTO_SRCS ${pb_cc} ${grpc_pb_cc})  # Append generated source files to the list
    list(APPEND PROTO_HDRS ${pb_h} ${grpc_pb_h})  # Append generated header files to the list
endforeach ()

add_custom_target(generate_proto ALL DEPENDS ${PROTO_SRCS} ${PROTO_HDRS})  # Create a custom target to generate all gRPC code