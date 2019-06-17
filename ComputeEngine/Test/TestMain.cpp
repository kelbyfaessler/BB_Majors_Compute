//Demo to familiarize with google test framework

#include <gtest\gtest.h>

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();
    std::getchar(); //keep console window open
}