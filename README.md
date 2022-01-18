# 专门针对中文文档的simhash算法库 [English](README_EN.md) 

[![CMake](https://github.com/yanyiwu/simhash/actions/workflows/cmake.yml/badge.svg)](https://github.com/yanyiwu/simhash/actions/workflows/cmake.yml)
[![Build Status](https://travis-ci.org/yanyiwu/simhash.png?branch=master)](https://travis-ci.org/yanyiwu/simhash)
[![Platform](https://img.shields.io/badge/platform-Linux,%20OS%20X,%20Windows-green.svg?style=flat)](https://github.com/yanyiwu/simhash)
[![Author](https://img.shields.io/badge/author-@yanyiwu-blue.svg?style=flat)](http://yanyiwu.com/) 
[![License](https://img.shields.io/badge/license-MIT-yellow.svg?style=flat)](http://yanyiwu.mit-license.org)
[![Tag](https://img.shields.io/github/v/tag/yanyiwu/simhash.svg)](https://github.com/yanyiwu/simhash/releases)
[![logo](http://images.yanyiwu.com/SimhashLogo-v1.png)](https://github.com/yanyiwu/simhash)

## 简介

此项目用来对中文文档计算出对应的 simhash 值。 simhash 是谷歌用来进行文本去重的算法，现在广泛应用在文本处理中。

详见[simhash算法原理及实现]

## 特性

+ 使用 [CppJieba] 作为分词器和关键词抽取器
+ 使用 [jenkins] 作为 hash 函数
+ `hpp` 风格，所有源码都是 `.hpp` 文件里面，方便使用。 `没有链接，就没有伤害。`
+ 本项目的副产品项目：[simhash\_server] 提供了简单的 simhash HTTP 服务。

## 依赖

* g++ (version >= 4.1 recommended), or clang++ . 

## 用法

```sh
mkdir build
cd build
cmake ..
make
```

测试

```
make test
```

### 演示

```sh
./demo
```

结果如下：

```
文本："我是蓝翔技工拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上总经理，出任CEO，走上人生巅峰。"
关键词序列是: ["蓝翔:11.7392", "CEO:11.7392", "升职:10.8562", "加薪:10.6426", "手扶拖拉机:10.0089"]
simhash值是: 17831459094038722629
100010110110和110001110011 simhash值的相等判断如下：
海明距离阈值默认设置为3，则isEqual结果为：0
海明距离阈值默认设置为5，则isEqual结果为：1
```

详情请看 [example/demo.cpp](example/demo.cpp)

### Benchmark
```sh
./benchmark/benchmarking
```
结果如下:
```
Running ./benchmark/benchmarking
Run on (16 X 2494.14 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x16)
  L1 Instruction 32 KiB (x16)
  L2 Unified 4096 KiB (x16)
  L3 Unified 36608 KiB (x1)
Load Average: 0.07, 0.04, 0.03
***WARNING*** Library was built as DEBUG. Timings may be affected.
-------------------------------------------------------------------------------------------------
Benchmark                                                       Time             CPU   Iterations
-------------------------------------------------------------------------------------------------
BENCHMARK_Simhasher_extract_text50_top5                     13478 ns        13478 ns        52013
BENCHMARK_Simhasher_extract_text50_top10                    13843 ns        13843 ns        50833
BENCHMARK_Simhasher_extract_text50_top15                    13929 ns        13929 ns        49488
BENCHMARK_Simhasher_extract_text50_top20                    13842 ns        13842 ns        50541
BENCHMARK_Simhasher_extract_text500_top5                   184074 ns       184067 ns         3775
BENCHMARK_Simhasher_make_text50_top5                        14457 ns        14457 ns        48341
BENCHMARK_Simhasher_make_text50_top10                       15170 ns        15169 ns        46203
BENCHMARK_Simhasher_make_text50_top15                       15585 ns        15585 ns        44903
BENCHMARK_Simhasher_make_text50_top20                       15743 ns        15742 ns        44466
BENCHMARK_Simhasher_binaryStringToUint64                    0.000 ns        0.000 ns   1000000000
BENCHMARK_Simhasher_toBinaryString                           63.9 ns         63.9 ns     10937009
BENCHMARK_Simhasher_make_from_predefined_keywords5            423 ns          423 ns      1644823
BENCHMARK_Simhasher_make_from_predefined_keywords10           735 ns          735 ns       950156
BENCHMARK_Simhasher_make_from_predefined_keywords20          1364 ns         1364 ns       508935
BENCHMARK_Simhasher_make_from_predefined_keywords50          7876 ns         7875 ns        89006
BENCHMARK_Simhasher_make_from_predefined_keywords100        21409 ns        21409 ns        32743
BENCHMARK_Simhasher_make_from_predefined_keywords200        47469 ns        47468 ns        14728
BENCHMARK_Simhasher_make_from_predefined_keywords500       124316 ns       124314 ns         5627
BENCHMARK_Simhasher_make_from_predefined_keywords1000      251336 ns       251329 ns         2785
BENCHMARK_Simhasher_binaryStringToUint64_isEqual            0.000 ns        0.000 ns   1000000000
BENCHMARK_Simhasher_binaryStringToUint64_isEqual_10k        0.000 ns        0.000 ns   1000000000
BENCHMARK_Simhasher_binaryStringToUint64_isEqual_1000k      0.000 ns        0.000 ns   1000000000
```

## 客服

+ Email: `i@yanyiwu.com`
+ QQ: 64162451

![image](http://7viirv.com1.z0.glb.clouddn.com/5a7d1b5c0d_yanyiwu_personal_qrcodes.jpg)

[simhash算法原理及实现]:http://yanyiwu.com/work/2014/01/30/simhash-shi-xian-xiang-jie.html
[CppJieba]:https://github.com/yanyiwu/cppjieba
[jenkins]:https://github.com/seomoz/simhash-cpp/blob/master/src/hashes/jenkins.h
[simhash\_server]:https://github.com/yanyiwu/simhash_server



