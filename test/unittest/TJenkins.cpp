#include "simhash/jenkins.h"
#include "gtest/gtest.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace simhash;

TEST(JenkinsTest, Test1)
{
    jenkins hasher;
    ifstream ifs("../test/testdata/news_content");
    string doc((istreambuf_iterator<char>(ifs)), istreambuf_iterator<char>());
    //cout<< doc<<endl;
    ASSERT_EQ(uint64_t(13697483439902700582U), hasher(doc.c_str(), doc.size(), 0));
    ASSERT_EQ(uint64_t(13697483439902700582U), hasher(doc.c_str(), doc.size(), 0));
}


