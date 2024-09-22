cmake_minimum_required(VERSION 3.14)

PROJECT(simhash)

# Define a variable to check if this is the top-level project
if(NOT DEFINED simhash_TOP_LEVEL_PROJECT)
    if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(simhash_TOP_LEVEL_PROJECT ON)
    else()
        set(simhash_TOP_LEVEL_PROJECT OFF)
    endif()
endif()

option(simhash_BUILD_TESTS "Build simhash tests" ${simhash_TOP_LEVEL_PROJECT})

if(simhash_BUILD_TESTS)
	#OPTION(BENCHMARK "Build benchmarking library" ON)

	INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/submodules/cppjieba/include
	  ${PROJECT_SOURCE_DIR}/submodules/cppjieba/deps/limonp/include
	  ${PROJECT_SOURCE_DIR}/include)

	ADD_DEFINITIONS(-O3 -g)

	if(NOT DEFINED CMAKE_CXX_STANDARD)
	    set(CMAKE_CXX_STANDARD 11)
	endif()

	ADD_SUBDIRECTORY(test)
	ADD_SUBDIRECTORY(benchmark)

	ENABLE_TESTING()
	ADD_TEST(NAME ./test/test.run COMMAND ./test/test.run)
	ADD_TEST(NAME ./test/load_test COMMAND ./test/load_test)
endif()
