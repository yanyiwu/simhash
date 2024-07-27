CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

PROJECT(simhash)

#OPTION(BENCHMARK "Build benchmarking library" ON)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/submodules/cppjieba/include
  ${PROJECT_SOURCE_DIR}/submodules/cppjieba/deps/limonp/include
  ${PROJECT_SOURCE_DIR}/include)

ADD_DEFINITIONS(-O3 -Wall -g)
IF(APPLE) 
    ADD_DEFINITIONS(-std=c++11)
endif()

ADD_SUBDIRECTORY(example)
ADD_SUBDIRECTORY(test)
ADD_SUBDIRECTORY(benchmark)

ENABLE_TESTING()
ADD_TEST(NAME ./test/test.run COMMAND ./test/test.run)
ADD_TEST(NAME ./test/load_test COMMAND ./test/load_test)
ADD_TEST(NAME ./demo COMMAND ./demo)
