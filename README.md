# simhash  

## 概述

此项目用来对中文文档计算出对于的simhash值

[simhash] 是谷歌用来进行文本去重的算法，现在广泛应用在文本处理中。

在计算simhash的过程中我们需要对文本进行分词和关键词抽取，这部分使用[CppJieba]来完成。

对于hash算法直接采用[jenkins]，少量修改。


## 你可能需要安装的

* cmake(version >= 2.8)
* g++ (version >= 4.7)


## 运行和使用

```sh
mkdir build
cd build
cmake ..
make
```

### demo 

```sh
./bin/simhash.demo
```

you will see:

```
文本："我是蓝翔技工拖拉机学院手扶拖拉机专业的。不用多久，我就会升职加薪，当上总经理，出任CEO，迎娶白富 美，走上人生巅峰。"
关键词序列是: ["CEO:11.7392", "白富美:11.7392", "蓝翔:11.7392", "迎娶:10.0505", "加薪:10.6426"]
simhash值是: 18002950507231148557
```

### 用法

功能代码都写成hpp文件，直接include即可使用。

上面的 `simhash.demo` 是由 `src/main.cpp` 生成。

所以关于simhash的用法请看`src/main.cpp`，很简单，就几行代码。

## 客服

wuyanyi09@gmail.com


[CppJieba]:https://github.com/aszxqw/cppjieba
[jenkins]:https://github.com/seomoz/simhash-cpp/blob/master/src/hashes/jenkins.h
[simhash]:http://leoncom.org/?p=650607
