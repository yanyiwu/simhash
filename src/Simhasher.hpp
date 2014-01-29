#ifndef SIMHASH_SIMHASH_H
#define SIMHASH_SIMHASH_H

#include "CppJieba/KeywordExtractor.hpp"
#include "hashes/jenkins.h"

namespace Simhash
{
    using namespace CppJieba;
    class Simhasher: public InitOnOff
    {
        private:
            enum{BITS_LENGTH = 64};
            jenkins _hasher;
            KeywordExtractor _keywordExtor;
        public:
            Simhasher(const string& dictPath, const string& idfPath): _keywordExtor(dictPath, idfPath)
            {_setInitFlag(_keywordExtor);}
            ~Simhasher(){};
        public:
            bool extract(const string& text, vector<pair<string,double> > & res, uint topN) const
            {
                return _keywordExtor.extract(text, res, topN);
            }
            bool make(const string& text, uint topN, vector<pair<uint64_t, double> >& res) const
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

            bool make(const string& text, uint topN, uint64_t& v64) const
            {
                vector<pair<uint64_t, double> > hashvalues;
                if(!make(text, topN, hashvalues))
                {
                    return false;
                }
                vector<double> weights(BITS_LENGTH, 0.0);
                const uint64_t u64_1(1);
                for(uint i = 0; i < hashvalues.size(); i++)
                {
                    for(uint j = 0; j < BITS_LENGTH; j++)
                    {
                        if(((u64_1 << j) & hashvalues[i].first))
                        {
                            weights[j] += hashvalues[i].second;
                        }
                        else
                        {
                            weights[j] -= hashvalues[i].second;
                        }
                    }
                }

                v64 = 0;
                for(uint j = 0; j < BITS_LENGTH; j++)
                {
                    if(weights[j] > 0.0)
                    {
                        v64 |= (u64_1 << j);
                    }
                }
                
                return true;
            }
    };
}

#endif


