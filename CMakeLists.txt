PROJECT(simhash)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

OPTION(BENCHMARK "Build benchmarking library" ON)
OPTION(PYBIND "Build python binding" OFF)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/deps
  ${PROJECT_SOURCE_DIR}/include)

ADD_DEFINITIONS(-O3 -Wall -g)
IF(APPLE) 
    ADD_DEFINITIONS(-std=c++11)
endif()

ADD_SUBDIRECTORY(example)
ADD_SUBDIRECTORY(test)
ADD_SUBDIRECTORY(benchmark)
ADD_SUBDIRECTORY(python)

ENABLE_TESTING()
ADD_TEST(NAME ./test/test.run COMMAND ./test/test.run)
ADD_TEST(NAME ./test/load_test COMMAND ./test/load_test)
ADD_TEST(NAME ./demo COMMAND ./demo)
