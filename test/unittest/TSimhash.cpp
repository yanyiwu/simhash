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

    //print(Simhasher::toBinaryString(u1));
    //print(Simhasher::toBinaryString(u2));
    //exit(1);
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
    
    //print(Simhasher::toBinaryString(u1));
    //print(Simhasher::toBinaryString(u2));
    //exit(1);
}

TEST(SimhasherTest, Test6)
{
    Simhasher simhasher("../dict/jieba.dict.utf8", "../dict/hmm_model.utf8", "../dict/idf.utf8");
    string s("我是蓝翔技工拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上总经理，出任CEO，迎娶白富美，走上人生巅峰。");
    string s2("我是蓝翔技工拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上总经理，出任CEO，迎娶白富美，走上人生巅峰，加薪。");
    string res;
    uint topN = 5;
    uint64_t u;
    uint64_t u2;
    vector<pair<string, double> > wordweights;
    vector<pair<string, double> > wordweights2;
    simhasher.extract(s, wordweights, topN);
    simhasher.extract(s2, wordweights2, topN);
    res << wordweights;
    //print(res);
    ASSERT_EQ(res, "[\"CEO:11.7392\", \"蓝翔:11.7392\", \"白富美:11.7392\", \"升职:10.8562\", \"加薪:10.6426\"]");
    res << wordweights2;
    //print(res);
    
    simhasher.make(s, topN, u);
    simhasher.make(s2, topN, u2);
    //print(Simhasher::toBinaryString(u));
    //print(Simhasher::toBinaryString(u2));
    ASSERT_EQ(u, u2);
}


TEST(SimhasherTest, Test7)
{
    uint64_t u1, u2;
    u1 = Simhasher::binaryStringToUint64("100010110110"); 
    u2 = Simhasher::binaryStringToUint64("110001110011"); 
    ASSERT_FALSE(Simhasher::isEqual(u1, u2)); // default 3
    ASSERT_TRUE(Simhasher::isEqual(u1, u2, 5));
    u1 = Simhasher::binaryStringToUint64("100010110110"); 
    u2 = Simhasher::binaryStringToUint64("110010110111"); 
    ASSERT_TRUE(Simhasher::isEqual(u1, u2));
    
}

