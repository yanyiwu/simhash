#include "src/hashes/jenkins.h"
#include "gtest/gtest.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace SimhashSpace;

TEST(JenkinsTest, Test1)
{
    jenkins hasher;
    ifstream ifs("../test/testdata/news_content");
    ASSERT_TRUE(ifs);
    string doc((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
    //cout<< doc<<endl;
    ASSERT_EQ(uint64_t(13697483439902700582U), hasher(doc.c_str(), doc.size(), 0));
}


