# Project
set(TEST_FOR_FRAMEWORK test_project)
project(${TEST_FOR_FRAMEWORK})

# Includes
include_directories(../common)

file(GLOB_RECURSE SRC_TEST_CASES
        *.cc
)

# Executable
add_executable(${TEST_FOR_FRAMEWORK}
        ${FRAMEWORK_FILES}
        ${SRC_TEST_CASES}
)

# Link
target_link_libraries(${TEST_FOR_FRAMEWORK} PRIVATE
        GTest::gtest_main GTest::gtest
        glog::glog
        Boost::headers
        yaml-cpp::yaml-cpp
        RapidJSON rapidjson
        OpenSSL::SSL OpenSSL::Crypto
        ${COMMON_FRAMEWORK}
)