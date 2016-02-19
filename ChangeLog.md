# Simhash ChangeLog

## next version

+ add new directory: `deps` for `cppjieba` and `limonp`
+ change `namespace Simhash` to `namespace simhash` 
+ mv `src/main.cpp` to `example/demo.cpp`
+ mv `src/` to `include/`

## v0.9.6

1. 升级 [CppJieba] 到 v4.1.2 版本。

## v0.9.5

1. 使用[CppJieba] v3.0.1 ，修复一些兼容性问题。

## v0.9.4

1. 更新[CppJieba]用以适配更加低版本的g++。
2. 更新[CppJieba]用以引入在关键词抽取过程中使用停用词(dict/stop_words.utf8)。
3. 增加性能测试。
4. 更新`KeywordExtractor`提高关键词抽取的速度，性能约提高1.3倍。


## v0.9.3

1. 更新[CppJieba]用以修复关于头文件包含的小bug

## v0.9.2

1. 完成simhash海明距离的计算
2. 修复关键词抽取后权重排序的bug

## v0.9.1

1. 完成分词，关键词抽取，simhash值计算的基本功能

[CppJieba]:https://github.com/yanyiwu/cppjieba.git
