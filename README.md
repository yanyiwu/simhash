[![Build Status](https://travis-ci.org/yanyiwu/simhash.png?branch=master)](https://travis-ci.org/yanyiwu/simhash)
- - -

# 专门针对中文文档的simhash算法库

## 简介

此项目用来对中文文档计算出对应的 simhash 值。 simhash 是谷歌用来进行文本去重的算法，现在广泛应用在文本处理中。

详见[simhash算法原理及实现]

## 特性

+ 使用 [CppJieba] 作为分词器和关键词抽取器
+ 使用 [jenkins] 作为 hash 函数
+ `hpp` 风格，所有源码都是 `.hpp` 文件里面，方便使用。 `没有链接，就没有伤害。`

## 依赖

* g++ (version >= 4.1 recommended), or clang++ . 

## 用法

```sh
mkdir build
cd build
cmake ..
make
```

### 演示

```sh
./bin/simhash.demo
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

详情请看 `src/main.cpp`

## 客服

`i@yanyiwu.com`

[simhash算法原理及实现]:http://yanyiwu.com/work/2014/01/30/simhash-shi-xian-xiang-jie.html
[CppJieba]:https://github.com/yanyiwu/cppjieba
[jenkins]:https://github.com/seomoz/simhash-cpp/blob/master/src/hashes/jenkins.h
