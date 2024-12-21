enable_testing()

set(SRC_TEST_FILES "")
foreach (FILE ${SRC_FILES})
    if (NOT FILE MATCHES ".*/app/.*")
        list(APPEND SRC_TEST_FILES ${FILE})
    endif ()
endforeach ()

set(SRC_TEST_DIR ./test)
file(GLOB_RECURSE SRC_TEST_CASES
        ${SRC_TEST_DIR}/*.cpp
)

add_executable(gtest
        ${SRC_TEST_FILES}
        ${SRC_TEST_CASES}
)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(gtest PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main)
