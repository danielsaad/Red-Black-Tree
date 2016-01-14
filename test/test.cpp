#include <iostream>

#include "gtest/gtest.h"

TEST(sample_test_case, sample_test)
{
    EXPECT_EQ(1, 1);
}

int main() {     
	testing::InitGoogleTest(&argc, argv); 
    RUN_ALL_TESTS(); 
}
