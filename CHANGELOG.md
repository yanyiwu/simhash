# ChangeLog

## v1.2.3

+ class Simhasher: using cppjieba::Jieba instead of cppjieba::keywordextractor
+ [submodule/cppjieba] v5.3.1 -> v5.4.0
+ cmake: avoid testing when FetchContent by other project
+ [stale-issues] stale 1 year ago

## v1.2.2

+ [googletest] removed submodule and add cmake-fetchcontent
+ [submodule] cppjieba v5.3.0 -> v5.3.1

## v1.2.1

+ [submodule] cppjieba v5.1.2 -> v5.3.0
+ [CI] macos,linux and c++[11,14,17,20]
+ [CMake] mini_required 2.6->3.5

## v1.2.0

+ [googletest] git submodule add googletest-1.6.0

## v1.1.1

+ [submodule] add submodules/cppjieba, and remove deps/cppjieba/ and remove dict/

## v1.1.0

+ [submodule] using git submodule, and add submodules/limonp.
+ [pr-28] merged.
+ [pr-27] merged.
+ [pr-26] merged.
+ [pr-21] merged.

## v1.0.0

+ [deps] update limonp to v0.6.2

## v0.10.1

+ upgrade cppjieba to v4.5.3

## v0.10.0

+ add new directory: `deps` for `cppjieba` and `limonp`
+ change `namespace Simhash` to `namespace simhash` 
+ mv `src/main.cpp` to `example/demo.cpp`
+ mv `src/` to `include/`

+ upgrade limonp to v0.5.4
+ upgrade cppjieba to v4.5.0

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
