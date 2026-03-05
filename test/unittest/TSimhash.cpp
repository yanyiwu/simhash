#include "simhash/Simhasher.hpp"
#include "gtest/gtest.h"

using namespace simhash;

static bool loadFile2Str(const string& filePath, string& s)
{
    ifstream ifs(filePath.c_str());
    if(!ifs)
    {
        return false;
    }
    s << ifs;
    return true;
}

TEST(SimhasherTest, Test1)
{
    Simhasher shash("../submodules/cppjieba/dict/jieba.dict.utf8", "../submodules/cppjieba/dict/hmm_model.utf8", "../submodules/cppjieba/dict/idf.utf8", "../submodules/cppjieba/dict/stop_words.utf8");
    {
        string s;
        ASSERT_TRUE(loadFile2Str("../test/testdata/news_content", s));
        vector<pair<uint64_t, double> > v64s;
        ASSERT_TRUE(shash.make(s, 5, v64s));
        string res;
        res << v64s;
        //ASSERT_EQ(res, "[\"15142046212652221781:318.452\", \"2117559126361955906:151.001\", \"14814508906697812479:140.87\", \"13004687738940023035:106.978\", \"18264030747823598625:103.739\"]");
        ASSERT_EQ(res, "[15142046212652221781:318.452, 2117559126361955906:151.001, 14814508906697812479:140.87, 13004687738940023035:106.978, 18264030747823598625:103.739]");
    }
    {
        uint64_t u64;
        string s;
        ASSERT_TRUE(loadFile2Str("../test/testdata/news_content", s));
        ASSERT_TRUE(shash.make(s, 5, u64));
        string res;
        res << u64;
        ASSERT_EQ("15286165794479097173", res);
    }
    {
        uint64_t u1, u2;
        string s1, s2;
        ASSERT_TRUE(loadFile2Str("../test/testdata/news_content", s1));
        ASSERT_TRUE(shash.make(s1, 50, u1));
        ASSERT_TRUE(loadFile2Str("../test/testdata/news_content.2", s2));
        ASSERT_TRUE(shash.make(s2, 50, u2));
        ASSERT_EQ(u1, u2);
    }
    {
        uint64_t u1, u2;
        string s1, s2;
        ASSERT_TRUE(loadFile2Str("../test/testdata/news_content.3", s1));
        ASSERT_TRUE(shash.make(s1, 50, u1));
        ASSERT_TRUE(loadFile2Str("../test/testdata/news_content.4", s2));
        ASSERT_TRUE(shash.make(s2, 50, u2));
        ASSERT_EQ(u1, u2);
    }
    {
        uint64_t u1, u2;
        string s1, s2;
        ASSERT_TRUE(loadFile2Str("../test/testdata/news_content.2", s1));
        ASSERT_TRUE(shash.make(s1, 50, u1));
        ASSERT_TRUE(loadFile2Str("../test/testdata/news_content.3", s2));
        ASSERT_TRUE(shash.make(s2, 50, u2));
        ASSERT_NE(u1, u2);
    }
    {
        uint64_t u1;
        const char * const sentence = "你好世界";
        //vector<pair<string, double> > res;
        shash.make(sentence, 3, u1);
        string s;
        s << u1;
        ASSERT_EQ(s, "17676873585679812141");
    }
}

TEST(SimhasherTest, Test2)
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

TEST(SimhasherTest, TestGetTopN)
{
    // Very short text should return the minimum topN of 5.
    string shortText(100, 'a');
    ASSERT_EQ(Simhasher::getTopN(shortText), (size_t)5);

    // Text of exactly 600 bytes: 600/120 = 5 → still 5 (minimum).
    string text600(600, 'a');
    ASSERT_EQ(Simhasher::getTopN(text600), (size_t)5);

    // Text of 1200 bytes: 1200/120 = 10.
    string text1200(1200, 'a');
    ASSERT_EQ(Simhasher::getTopN(text1200), (size_t)10);

    // Text of 7800 bytes: 7800/120 = 65.
    string text7800(7800, 'a');
    ASSERT_EQ(Simhasher::getTopN(text7800), (size_t)65);

    // Very long text should be capped at the maximum topN of 200.
    string longText(30000, 'a');
    ASSERT_EQ(Simhasher::getTopN(longText), (size_t)200);
}

TEST(SimhasherTest, TestAdaptiveMake)
{
    Simhasher shash("../submodules/cppjieba/dict/jieba.dict.utf8", "../submodules/cppjieba/dict/hmm_model.utf8", "../submodules/cppjieba/dict/idf.utf8", "../submodules/cppjieba/dict/stop_words.utf8");

    // Verify that the adaptive make() overload (no explicit topN) produces the same
    // result as calling make() with getTopN() explicitly.
    string s;
    ASSERT_TRUE(loadFile2Str("../test/testdata/news_content", s));

    uint64_t u_adaptive, u_explicit;
    ASSERT_TRUE(shash.make(s, u_adaptive));
    ASSERT_TRUE(shash.make(s, Simhasher::getTopN(s), u_explicit));
    ASSERT_EQ(u_adaptive, u_explicit);
}

