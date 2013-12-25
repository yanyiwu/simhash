#include "src/Simhash.hpp"
#include "gtest/gtest.h"

using namespace SimhashSpace;

TEST(SimhashTest, Test1)
{
    Simhash shash("../dict/jieba.dict.utf8", "../dict/idf.utf8");
    ASSERT_TRUE(shash);
    const char* str = "我来自北京邮电大学。。。  学号 123456";
    const char* res[] = {"我来", "自北京", "邮电大学", "。", "。", "。", "  ", "学号", " 123456"};
    //string s;
    //vector<string> buf(res, res + sizeof(res)/sizeof(res[0]));
    //vector<string> words;
    //ASSERT_TRUE(shash);
    //ASSERT_TRUE(shash.make(str, words, ));
    ////print(words);
    //EXPECT_EQ(words, vector<string>(res, res + sizeof(res)/sizeof(res[0])));
}

