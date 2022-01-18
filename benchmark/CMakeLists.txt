# file: CMakeLists.txt
# date: 2022-01-18


if(${CMAKE_VERSION} VERSION_GREATER "3.16.0" 
        AND BENCHMARK)
    message(
        STATUS 
        "CMake version is eligible for benchmarking and benchmarking flag is '${BENCHMARK}'.")
    
    include(FetchContent)
    set(FETCHCONTENT_QUIET FALSE)

    FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com.cnpmjs.org/google/benchmark.git 
        GIT_TAG v1.6.1
        GIT_PROGRESS TRUE
    )
    set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
    FetchContent_MakeAvailable(googlebenchmark)

    add_executable(benchmarking ./benchmarking.cpp)
    target_link_libraries(benchmarking benchmark::benchmark)
endif()
