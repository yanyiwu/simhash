# SimHash C++ Lib Specially For Chinese Document [简体中文](README.md) 

[![Build Status](https://travis-ci.org/yanyiwu/simhash.png?branch=master)](https://travis-ci.org/yanyiwu/simhash)
[![Platform](https://img.shields.io/badge/platform-Linux,%20OS%20X,%20Windows-green.svg?style=flat)](https://github.com/yanyiwu/simhash)
[![Author](https://img.shields.io/badge/author-@yanyiwu-blue.svg?style=flat)](http://yanyiwu.com/) 
[![License](https://img.shields.io/badge/license-MIT-yellow.svg?style=flat)](http://yanyiwu.mit-license.org)

## Introduction

This project is made for SimHash calculation in Chinese documents, SimHash is the text de-duplication algorithm in Google.
Now it has been widely used in Text Processing.

Please see more details in [simhash算法原理及实现] .

## Feature

+ Use [CppJieba] as Tokenizer and Keyword Extractor.
+ Use [jenkins] as the Hash function.
+ C++ `hpp` style, all the codes are written in header files, so anyone can use them without linking, `No linking, no hurts`.

## Dependencies

* g++ (version >= 4.1 recommended), or clang++ . 

## Usage

```sh
mkdir build
cd build
cmake ..
make
```

Test:

```
make test
```

### Demo

```sh
./demo
```

Output Result:

```
文本："我是蓝翔技工拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上总经理，出任CEO，走上人生巅峰。"
关键词序列是: ["蓝翔:11.7392", "CEO:11.7392", "升职:10.8562", "加薪:10.6426", "手扶拖拉机:10.0089"]
simhash值是: 17831459094038722629
100010110110和110001110011 simhash值的相等判断如下：
海明距离阈值默认设置为3，则isEqual结果为：0
海明距离阈值默认设置为5，则isEqual结果为：1
```

See details in [example/demo.cpp](example/demo.cpp)

## Contact

+ Email: `i@yanyiwu.com`
+ QQ: 64162451

![image](http://7viirv.com1.z0.glb.clouddn.com/5a7d1b5c0d_yanyiwu_personal_qrcodes.jpg)

[simhash算法原理及实现]:http://yanyiwu.com/work/2014/01/30/simhash-shi-xian-xiang-jie.html
[CppJieba]:https://github.com/yanyiwu/cppjieba
[jenkins]:https://github.com/seomoz/simhash-cpp/blob/master/src/hashes/jenkins.h
[simhash\_server]:https://github.com/yanyiwu/simhash_server
