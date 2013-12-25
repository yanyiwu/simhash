#ifndef SIMHASH_SIMHASH_H
#define SIMHASH_SIMHASH_H

#include "CppJieba/KeywordExtractor.hpp"

namespace SimhashSpace
{
    using namespace CppJieba;
    class Simhash: public KeywordExtractor
    {
        public:
            Simhash(const string& dictPath, const string& idfPath): KeywordExtractor(dictPath, idfPath)
            {
            }
            ~Simhash(){};
        public:
            bool dispose(){return false;};
        public:
            bool make(const string& text, uint64_t & v64, uint topN)
            {
                vector<pair<string, double> > wordweights;
                return extract(text, wordweights, topN);
            }
    };
}

#endif


