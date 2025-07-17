#project
set(TEST_PROJECT test_project)
project(${TEST_PROJECT})

#includes
include_directories(../coco)

file(GLOB_RECURSE SRC_TEST_CASES
        *.cc
)

#executable
add_executable(${TEST_PROJECT}
        ${FRAMEWORK_FILES}
        ${SRC_TEST_CASES}
)

#link
target_link_libraries(${TEST_PROJECT} PRIVATE
        GTest::gtest_main GTest::gtest
        glog::glog
        Boost::system
        Boost::thread
        Boost::url
        Boost::asio
        yaml-cpp::yaml-cpp
        RapidJSON rapidjson
        OpenSSL::SSL OpenSSL::Crypto
        coco
)