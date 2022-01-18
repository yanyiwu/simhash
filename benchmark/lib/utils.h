/// file: utils.h
/// date: 2022-01-18


#ifndef __UTILS_H__
#define __UTILS_H__

#include <vector>
#include <utility>
#include <string>


namespace simhash_benchmark {


std::vector<std::pair<std::string, double> > fake_keywords(
    int32_t num) {
  std::vector<std::pair<std::string, double> > keywords;
  double score = 1.0 / (double)num;
  for (int32_t i = 0; i < num; ++i) {
    std::string keyword = "fake_" + std::to_string(i);
    keywords.emplace_back(std::make_pair(keyword, score));
  }
  return keywords;
}


} // namespace simhash_benchmark 


#endif
