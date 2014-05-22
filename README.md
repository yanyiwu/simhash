[![Build Status](https://travis-ci.org/aszxqw/simhash.png?branch=master)](https://travis-ci.org/aszxqw/simhash)
- - -

# 专门针对中文文档的simhash算法库

## Introduction

此项目用来对中文文档计算出对于的simhash值。simhash是谷歌用来进行文本去重的算法，现在广泛应用在文本处理中。

详见[SimhashBlog]

## Feature

+ use [CppJieba] as Chinese Word Segmentor and Keyword Extractor.
+ use [jenkins] as hash function.
+ written by `hpp` stype. In other words , all useful codes are in header files.  You can use them only by `include` them.  `No Linking , No hurts.`

## Dependency

* g++ (version >= 4.1 recommended), or clang++ . 

## Usage

```sh
mkdir build
cd build
cmake ..
make
```

### Demo

```sh
./bin/simhash.demo
```

you will see:

```
文本："我是蓝翔技工拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上总经理，出任CEO，走上人生巅峰。"
关键词序列是: ["蓝翔:11.7392", "CEO:11.7392", "升职:10.8562", "加薪:10.6426", "手扶拖拉机:10.0089"]
simhash值是: 17831459094038722629
100010110110和110001110011 simhash值的相等判断如下：
海明距离阈值默认设置为3，则isEqual结果为：0
海明距离阈值默认设置为5，则isEqual结果为：1
```

See **details** in `src/main.cpp`.

## Contact

wuyanyi09@foxmail.com

[SimhashBlog]:http://www.aszxqw.com/jekyll/update/2014/01/30/simhash-shi-xian-xiang-jie.html
[CppJieba]:https://github.com/aszxqw/cppjieba
[jenkins]:https://github.com/seomoz/simhash-cpp/blob/master/src/hashes/jenkins.h
