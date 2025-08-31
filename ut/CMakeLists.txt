# Project
set(TEST_PROJECT test_project)
project(${TEST_PROJECT})

# Includes
include_directories(../common)

file(GLOB_RECURSE SRC_TEST_CASES
        *.cc
)

# Executable
add_executable(${TEST_PROJECT}
        ${FRAMEWORK_FILES}
        ${SRC_TEST_CASES}
)

# Link
target_link_libraries(${TEST_PROJECT} PRIVATE
        GTest::gtest_main GTest::gtest
        glog::glog
        ${Boost_INCLUDE_DIRS}
        yaml-cpp::yaml-cpp
        RapidJSON rapidjson
        OpenSSL::SSL OpenSSL::Crypto
        common_pkg
)