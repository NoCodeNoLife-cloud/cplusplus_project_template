#include <glog/flags.h>
#include <glog/logging.h>
#include <gtest/gtest.h>

int main(int argc, char** argv)
{
    const std::string TEST_NAME = "all_test";
    google::InitGoogleLogging(TEST_NAME.c_str());
    FLAGS_logtostdout = true;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
