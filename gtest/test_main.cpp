#include <iostream>
#include <vector>
#include "rb_tree.hpp"
#include "gtest/gtest.h"

using namespace std;
using namespace algorithms;
TEST(sample_test_case, sample_test){
    vector<int> v;
    rb_tree<int> t;
    for(int i=0;i<1000;i++){
        t.insert(i);
        v.push_back(i);
    }
    t.print(t.root());
}

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv); 
    RUN_ALL_TESTS(); 
}
