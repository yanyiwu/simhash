#include "src/Simhash.hpp"
#include "gtest/gtest.h"

using namespace SimhashSpace;

TEST(SimhashTest, Test1)
{
    Simhash shash("../dict/jieba.dict.utf8", "../dict/idf.utf8");
    ASSERT_TRUE(shash);
    string s;
    ASSERT_TRUE(loadFile2Str("../test/testdata/news_content", s));
    vector<pair<uint64_t, double> > v64s;
    ASSERT_TRUE(shash.make(s, 5, v64s));
    string res;
    res << v64s;
    //print(v64s);
    ASSERT_EQ("[\"15142046212652221781:318.452\", \"2117559126361955906:151.001\", \"13004687738940023035:106.978\", \"18264030747823598625:103.739\", \"14309530273629218494:94.7993\"]", res);
}

