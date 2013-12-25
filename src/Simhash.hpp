#ifndef SIMHASH_SIMHASH_H
#define SIMHASH_SIMHASH_H

#include "CppJieba/KeywordExtractor.hpp"
#include "hashes/jenkins.h"

namespace SimhashSpace
{
    using namespace CppJieba;
    class Simhash: public KeywordExtractor
    {
        private:
            jenkins _hasher;
        public:
            Simhash(const string& dictPath, const string& idfPath): KeywordExtractor(dictPath, idfPath)
            {
            }
            ~Simhash(){};
        public:
            bool dispose(){return false;};
        public:
            bool make(const string& text, uint topN, vector<pair<uint64_t, double> >& res)
            {
                vector<pair<string, double> > wordweights;
                if(!extract(text, wordweights, topN))
                {
                    LogError("extract failed.");
                    return false;
                }
                res.clear();
                for(uint i = 0; i < wordweights.size(); i++)
                {
                    const string& word = wordweights[i].first;
                    res.push_back(make_pair(_hasher(word.c_str(), word.size(), 0), wordweights[i].second));
                }

                return true;
            }
    };
}

#endif


