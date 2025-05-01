#project
set(TEST_PROJECT test_project)
project(${TEST_PROJECT})

#includes
include_directories(../framework)

set(FRAMEWORK_DIR ../framework)
set(FRAMEWORK_HEADER_DIR ../framework)
file(GLOB_RECURSE FRAMEWORK_FILES
        ${FRAMEWORK_DIR}/*.hpp
        ${FRAMEWORK_HEADER_DIR}/*.cc
)

set(SRC_TEST_DIR test_case)
file(GLOB_RECURSE SRC_TEST_CASES
        ${SRC_TEST_DIR}/*.cc
)

#vcpkg dependencies
find_package(Boost REQUIRED COMPONENTS system thread url asio)
find_package(glog CONFIG REQUIRED)
find_package(gtest CONFIG REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(RapidJSON CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

#executable
add_executable(${TEST_PROJECT}
        ${FRAMEWORK_FILES}
        ${SRC_TEST_CASES}
)

#link
target_link_libraries(${TEST_PROJECT} PRIVATE GTest::gtest_main GTest::gtest)
target_link_libraries(${TEST_PROJECT} PRIVATE glog::glog)
target_link_libraries(${TEST_PROJECT} PRIVATE Boost::system)
target_link_libraries(${TEST_PROJECT} PRIVATE Boost::thread)
target_link_libraries(${TEST_PROJECT} PRIVATE Boost::url)
target_link_libraries(${TEST_PROJECT} PRIVATE Boost::asio)
target_link_libraries(${TEST_PROJECT} PRIVATE yaml-cpp::yaml-cpp)
target_link_libraries(${TEST_PROJECT} PRIVATE RapidJSON rapidjson)
target_link_libraries(${TEST_PROJECT} PRIVATE OpenSSL::SSL OpenSSL::Crypto)

#enable
enable_testing()
add_test(NAME RunAllTests COMMAND run_all_tests)