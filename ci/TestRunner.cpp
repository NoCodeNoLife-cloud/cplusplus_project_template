#include <glog/flags.h>
#include <glog/logging.h>
#include <gtest/gtest.h>

int main(int argc, char** argv)
{
    google::InitGoogleLogging("main");
    FLAGS_logtostdout = true;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
