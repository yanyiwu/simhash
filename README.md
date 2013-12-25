# simhash  

## 概述

此项目用来对中文文档计算出对于的simhash值

[simhash] 是谷歌用来进行文本去重的算法，现在广泛应用在文本处理中。

在计算simhash的过程中我们需要对文本进行分词和关键词抽取，这部门使用[CppJieba]来完成。

对于hash算法直接采用[jenkins]，少量修改。


## 依赖

* cmake
* g++ version >= 4.3




## 客服

wuyanyi09@gmail.com


[CppJieba]:https://github.com/aszxqw/cppjieba
[jenkins]:https://github.com/seomoz/simhash-cpp/blob/master/src/hashes/jenkins.h
[simhash]:http://leoncom.org/?p=650607
