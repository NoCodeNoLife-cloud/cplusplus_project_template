set(GTEST_NAME "gtest_ut")
project(GTEST_NAME)

# Find required packages
find_package(GTest REQUIRED)

# Source files collection
file(GLOB_RECURSE GTEST_SRC_FILES
        *.cc
)

# Create test executable with all discovered test files
add_executable(${GTEST_NAME}
        ${GTEST_SRC_FILES}
)

# Link required libraries
target_link_libraries(${GTEST_NAME}
        GTest::GTest
        GTest::Main
        ${COMMON_FRAMEWORK}
)

# Enable testing functionality
enable_testing()
