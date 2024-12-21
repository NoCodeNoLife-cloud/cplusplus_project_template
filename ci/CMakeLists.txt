#project
set(TEST_PROJECT test_template)
project(${TEST_PROJECT})

#enable
enable_testing()

#sources
set(SRC_TEST_FILES "")
foreach (FILE ${SRC_FILES})
    if (NOT FILE MATCHES ".*/app/.*")
        list(APPEND SRC_TEST_FILES ${FILE})
    endif ()
endforeach ()

set(SRC_TEST_DIR ./test)
file(GLOB_RECURSE SRC_TEST_CASES
        ${SRC_TEST_DIR}/*.cc
        TestBoost.cc
)

#executable
add_executable(${TEST_PROJECT}
        ${SRC_TEST_FILES}
        ${SRC_TEST_CASES}
)

#dependencies
find_package(glog CONFIG REQUIRED)
find_package(gtest CONFIG REQUIRED)

#link
target_link_libraries(${TEST_PROJECT} PRIVATE glog::glog)
target_link_libraries(${TEST_PROJECT} PRIVATE GTest::gtest_main)
target_link_libraries(${TEST_PROJECT} PRIVATE GTest::gmock)
target_link_libraries(${TEST_PROJECT} PRIVATE GTest::gmock_main)
target_link_libraries(${TEST_PROJECT} PRIVATE GTest::gtest)
