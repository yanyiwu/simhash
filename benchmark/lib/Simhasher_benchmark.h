/// file: Simhasher_benchmark.h
/// date: 2022-01-17


#ifndef __SIMHASHED_HENCHMARK_H__

#include <benchmark/benchmark.h>
#include "simhash/Simhasher.hpp"

#include "./vals.h"

using namespace simhash;


namespace simhash_benchmark {


int32_t top_n_keywords = 5;
uint64_t simhash64 = 0;
std::vector<std::pair<std::string, double> > keywords;


static void BENCHMARK_Simhasher_extract_text50_top5(
    benchmark::State& state) {
  keywords.clear();
  for (auto _ : state) {
    simhasher.extract(text50, keywords, 5);
  }
}


static void BENCHMARK_Simhasher_extract_text50_top10(
    benchmark::State& state) {
  keywords.clear();
  for (auto _ : state) {
    simhasher.extract(text50, keywords, 10);
  }
}


static void BENCHMARK_Simhasher_extract_text50_top15(
    benchmark::State& state) {
  keywords.clear();
  for (auto _ : state) {
    simhasher.extract(text50, keywords, 15);
  }
}


static void BENCHMARK_Simhasher_extract_text50_top20(
    benchmark::State& state) {
  keywords.clear();
  for (auto _ : state) {
    simhasher.extract(text50, keywords, 20);
  }
}


static void BENCHMARK_Simhasher_extract_text500_top5(
    benchmark::State& state) {
  keywords.clear();
  for (auto _ : state) {
    simhasher.extract(text500, keywords, 5);
  }
}


static void BENCHMARK_Simhasher_make_text50_top5(
    benchmark::State& state) {
  keywords.clear();
  for (auto _ : state) {
    simhasher.make(text50, 5, simhash64);
  }
}


static void BENCHMARK_Simhasher_make_text50_top10(
    benchmark::State& state) {
  keywords.clear();
  for (auto _ : state) {
    simhasher.make(text50, 10, simhash64);
  }
}


static void BENCHMARK_Simhasher_make_text50_top15(
    benchmark::State& state) {
  keywords.clear();
  for (auto _ : state) {
    simhasher.make(text50, 15, simhash64);
  }
}


static void BENCHMARK_Simhasher_make_text50_top20(
    benchmark::State& state) {
  keywords.clear();
  for (auto _ : state) {
    simhasher.make(text50, 20, simhash64);
  }
}


static void BENCHMARK_Simhasher_binaryStringToUint64(
    benchmark::State& state) {
  for (auto _ : state) {
    Simhasher::binaryStringToUint64(simhash_bin_str1); 
  }
}


static void BENCHMARK_Simhasher_toBinaryString(
    benchmark::State& state) {
  std::string res = "";
  for (auto _ : state) {
     Simhasher::toBinaryString(999999999, res);
  }
}


static void BENCHMARK_Simhasher_make_from_predefined_keywords5(
    benchmark::State& state) {
  for (auto _ : state) {
    Simhasher::make_from_predefined_keywords(keywords5);
  }
}


static void BENCHMARK_Simhasher_make_from_predefined_keywords10(
    benchmark::State& state) {
  for (auto _ : state) {
    Simhasher::make_from_predefined_keywords(keywords10);
  }
}


static void BENCHMARK_Simhasher_make_from_predefined_keywords20(
    benchmark::State& state) {
  for (auto _ : state) {
    Simhasher::make_from_predefined_keywords(keywords20);
  }
}


static void BENCHMARK_Simhasher_make_from_predefined_keywords50(
    benchmark::State& state) {
  for (auto _ : state) {
    Simhasher::make_from_predefined_keywords(keywords50);
  }
}


static void BENCHMARK_Simhasher_make_from_predefined_keywords100(
    benchmark::State& state) {
  for (auto _ : state) {
    Simhasher::make_from_predefined_keywords(keywords100);
  }
}


static void BENCHMARK_Simhasher_make_from_predefined_keywords200(
    benchmark::State& state) {
  for (auto _ : state) {
    Simhasher::make_from_predefined_keywords(keywords200);
  }
}


static void BENCHMARK_Simhasher_make_from_predefined_keywords500(
    benchmark::State& state) {
  for (auto _ : state) {
    Simhasher::make_from_predefined_keywords(keywords500);
  }
}


static void BENCHMARK_Simhasher_make_from_predefined_keywords1000(
    benchmark::State& state) {
  for (auto _ : state) {
    Simhasher::make_from_predefined_keywords(keywords1000);
  }
}


static void BENCHMARK_Simhasher_binaryStringToUint64_isEqual(
    benchmark::State& state) {
  for (auto _ : state) {
    Simhasher::isEqual(
        Simhasher::binaryStringToUint64(simhash_bin_str1), 
        Simhasher::binaryStringToUint64(simhash_bin_str2));
  }
}


void isEqual_n_times(int32_t n) {
  for (int32_t i = 0; i < n; ++i) {
    Simhasher::isEqual(
        Simhasher::binaryStringToUint64(simhash_bin_str1),
        Simhasher::binaryStringToUint64(simhash_bin_str2));
  }
}


static void BENCHMARK_Simhasher_binaryStringToUint64_isEqual_10k(
    benchmark::State& state) {
  for (auto _ : state) { isEqual_n_times(10000); }
}


static void BENCHMARK_Simhasher_binaryStringToUint64_isEqual_1000k(
    benchmark::State& state) {
  for (auto _ : state) { isEqual_n_times(1000000); }
}


} // simhash_benchmark

#endif


