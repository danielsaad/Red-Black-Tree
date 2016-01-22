#include <iostream>
#include <vector>
#include <random>
#include "rb_tree.hpp"
#include "gtest/gtest.h"

using namespace std;
using namespace algorithms;



class insert_text_fixture: public ::testing::Test{
protected:
    insert_text_fixture() {
        rng.seed(std::random_device()());
        distribution = std::uniform_int_distribution<std::mt19937::result_type>(1,MAX_VALUE); // distribution in range
        MAX_INSERT = 1e5;
        MAX_VALUE = 1e2;
    }

    void SetUp( ) {
    }

    void TearDown( ) {
    }

    ~insert_text_fixture()  {
    }
    size_t MAX_INSERT;
    size_t MAX_VALUE;
    std::mt19937 rng;
    std::uniform_int_distribution<std::mt19937::result_type> distribution;
    // put in any custom data members that you need
};


TEST_F(insert_text_fixture, insert_increasing){
    rb_tree<int> t;
    for(int i=0;i<MAX_INSERT;i++){
        t.insert(i);
    }
    EXPECT_EQ (true, t.assert_properties());
}


TEST_F(insert_text_fixture, insert_decreasing){
    rb_tree<int> t;
    for(int i=MAX_INSERT;i>=0;i--){
        t.insert(i);
    }
    EXPECT_EQ (true, t.assert_properties());
}


TEST_F(insert_text_fixture, insert_random){
    rb_tree<int> t;
    for(size_t i=0;i<MAX_INSERT;i++){
        t.insert(distribution(rng));
    }
    EXPECT_EQ (true, t.assert_properties());
}



int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv); 
    RUN_ALL_TESTS(); 
}
