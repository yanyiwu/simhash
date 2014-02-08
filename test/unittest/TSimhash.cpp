#include "src/Simhasher.hpp"
#include "gtest/gtest.h"

using namespace Simhash;

TEST(SimhasherTest, Test1)
{
    Simhasher shash("../dict/jieba.dict.utf8", "../dict/hmm_model.utf8", "../dict/idf.utf8");
    ASSERT_TRUE(shash);
    string s;
    ASSERT_TRUE(loadFile2Str("../test/testdata/news_content", s));
    vector<pair<uint64_t, double> > v64s;
    ASSERT_TRUE(shash.make(s, 5, v64s));
    string res;
    res << v64s;
    ASSERT_EQ(res, "[\"15142046212652221781:318.452\", \"2117559126361955906:151.001\", \"14814508906697812479:140.87\", \"13004687738940023035:106.978\", \"18264030747823598625:103.739\"]");
}

TEST(SimhasherTest, Test2)
{
    Simhasher shash("../dict/jieba.dict.utf8", "../dict/hmm_model.utf8", "../dict/idf.utf8");
    uint64_t u64;
    string s;
    ASSERT_TRUE(loadFile2Str("../test/testdata/news_content", s));
    ASSERT_TRUE(shash.make(s, 5, u64));
    string res;
    res << u64;
    ASSERT_EQ("15286165794479097173", res);
}

TEST(SimhasherTest, Test3)
{
    Simhasher shash("../dict/jieba.dict.utf8", "../dict/hmm_model.utf8", "../dict/idf.utf8");
    uint64_t u1, u2;
    string s1, s2;
    ASSERT_TRUE(loadFile2Str("../test/testdata/news_content", s1));
    ASSERT_TRUE(shash.make(s1, 50, u1));
    ASSERT_TRUE(loadFile2Str("../test/testdata/news_content.2", s2));
    ASSERT_TRUE(shash.make(s2, 50, u2));
    ASSERT_EQ(u1, u2);
}


TEST(SimhasherTest, Test4)
{
    Simhasher shash("../dict/jieba.dict.utf8", "../dict/hmm_model.utf8", "../dict/idf.utf8");
    uint64_t u1, u2;
    string s1, s2;
    ASSERT_TRUE(loadFile2Str("../test/testdata/news_content.3", s1));
    ASSERT_TRUE(shash.make(s1, 50, u1));
    ASSERT_TRUE(loadFile2Str("../test/testdata/news_content.4", s2));
    ASSERT_TRUE(shash.make(s2, 50, u2));
    ASSERT_EQ(u1, u2);
}


TEST(SimhasherTest, Test5)
{
    Simhasher shash("../dict/jieba.dict.utf8", "../dict/hmm_model.utf8", "../dict/idf.utf8");
    uint64_t u1, u2;
    string s1, s2;
    ASSERT_TRUE(loadFile2Str("../test/testdata/news_content.2", s1));
    ASSERT_TRUE(shash.make(s1, 50, u1));
    ASSERT_TRUE(loadFile2Str("../test/testdata/news_content.3", s2));
    ASSERT_TRUE(shash.make(s2, 50, u2));
    ASSERT_NE(u1, u2);
}

TEST(SimhasherTest, Test6)
{
    Simhasher simhasher("../dict/jieba.dict.utf8", "../dict/hmm_model.utf8", "../dict/idf.utf8");
    string s("我是蓝翔技工拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上总经理，出任CEO，迎娶白富美，走上人生巅峰。");
    string res;
    uint topN = 5;
    uint64_t u64;
    vector<pair<string, double> > wordweights;
    simhasher.extract(s, wordweights, topN);
    res << wordweights;
    ASSERT_EQ(res, "[\"CEO:11.7392\", \"白富美:11.7392\", \"蓝翔:11.7392\", \"迎娶:10.0505\", \"加薪:10.6426\"]");
    
    simhasher.make(s, topN, u64);
    ASSERT_EQ(u64, uint64_t(18002950507231148557u));
}

