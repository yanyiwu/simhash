
#include <iostream>
#include <fstream>

#define LOGGER_LEVEL LL_WARN //this define can avoid some logs which you dont care about.
#include "Simhasher.hpp"
using namespace Simhash;

int main(int argc, char** argv)
{
    Simhasher simhasher("../dict/jieba.dict.utf8", "../dict/idf.utf8");
    string s("我是蓝翔技工拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上总经理，出任CEO，迎娶白富美，走上人生巅峰。");
    uint topN = 5;
    uint64_t u64;
    simhasher.make(s, topN, u64);
    cout<< "[" << s << "] 的simhash值是: " << u64<<endl;
    return EXIT_SUCCESS;
}
