#include "src/Simhash.hpp"
#include "gtest/gtest.h"

using namespace SimhashSpace;

TEST(SimhashTest, Test1)
{
    Simhash shash("../dict/jieba.dict.utf8", "../dict/idf.utf8");
    ASSERT_TRUE(shash);
    string s;
    ASSERT_TRUE(loadFile2Str("../test/testdata/news_content", s));

}

