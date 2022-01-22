/// file: vals.h
/// date: 2022-01-18


#ifndef __VALS_H__
#define __VALS_H__

#include <benchmark/benchmark.h>
#include "simhash/Simhasher.hpp"
#include "./utils.h"


using namespace simhash;


namespace simhash_benchmark {


Simhasher simhasher(
  "../dict/jieba.dict.utf8", "../dict/hmm_model.utf8", 
  "../dict/idf.utf8", "../dict/stop_words.utf8");


/// Text with length 50 chars.
std::string text50 = 
    "我是蓝翔技工拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上总经理，出任CEO，走上人生巅峰。";


/// Text with length 500. 
/// Ref to 'https://mp.weixin.qq.com/s/Zdwb7Qo-044fVzO1Di2krw'.
std::string text500 = R"(
火山主要是因地壳板块推挤，岩浆中的气体压力到达一定程度造成喷发所致。海底火山与陆地火山原理相同，都是地球内部能量在地表的一种释放，也都有死火山与活火山之分。据不完全统计，目前全球的海底火山超过2万多座，其中太平洋拥有50%以上，是地球上火山最多、最密集的地方。

汤加位于世界第二深海沟汤加海沟（最深10882米）以及太平洋板块与印度—澳大利亚板块俯冲边界，是环太平洋地震带的地壳活动强烈区。地壳强烈活动使得汤加频繁遭遇地震和海底火山喷发。最近几年来，汤加里氏6级以上的大地震就发生过多次。

汤加的洪阿哈阿帕伊岛是汤加附近海底、汤加—克尔马德克群岛火山弧的一部分，坐落在新西兰东北向北延伸至斐济的地壳俯冲带。该处地壳十分活跃，火山近年多次喷发。汤加首席地质学家库拉认为，上一次喷发是在2021年12月20日，但那次的威力并不大，此次喷发释放的能量为上一次的7倍以上。

海底火山喷发的破坏是全方位的。喷发出来的火山气体，包括甲烷和硫化物等会溶到水中，对附近海底生态造成毁灭性打击。火山喷发导致汤加全境迅速被火山灰遮盖，空气和水严重污染，引发的海啸导致海水倒灌，居民无法正常生活。

由于汤加的海底电缆在火山喷发中断裂，导致汤加瞬间“失联”，目前灾情与人员伤亡数字仍无法统计。
)"; 


// Simhash bin strings.
std::string simhash_bin_str1 = "100010110110";
std::string simhash_bin_str2 = "110001110011";


// Pre-defined keywords
std::vector<std::pair<std::string, double> > keywords5 = fake_keywords(5);
std::vector<std::pair<std::string, double> > keywords10 = fake_keywords(10);
std::vector<std::pair<std::string, double> > keywords20 = fake_keywords(20);
std::vector<std::pair<std::string, double> > keywords50 = fake_keywords(50);
std::vector<std::pair<std::string, double> > keywords100 = fake_keywords(100);
std::vector<std::pair<std::string, double> > keywords200 = fake_keywords(200);
std::vector<std::pair<std::string, double> > keywords500 = fake_keywords(500); 
std::vector<std::pair<std::string, double> > keywords1000 = fake_keywords(1000); 


} // namespace simhash_benchmark

#endif
