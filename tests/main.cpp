#include "gtest/gtest.h"
#include <string>
#include "../src/network/threadFunctions.hpp"

TEST(header, header_test){

    std::string content = "siemano0";

    std::string withHeader = addHeader(content, 10);
    ASSERT_STREQ("0000000018siemano0", withHeader.c_str());
}



int main(int argc, char * argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}