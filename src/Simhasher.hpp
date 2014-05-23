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
            Simhasher(const string& dictPath, const string& modelPath, const string& idfPath, const string& stopWords): _keywordExtor(dictPath, modelPath, idfPath, stopWords)
            {_setInitFlag(_keywordExtor);}
            ~Simhasher(){};
        public:
            bool extract(const string& text, vector<pair<string,double> > & res, size_t topN) const
            {
                return _keywordExtor.extract(text, res, topN);
            }
            bool make(const string& text, size_t topN, vector<pair<uint64_t, double> >& res) const
            {
                vector<pair<string, double> > wordweights;
                if(!extract(text, wordweights, topN))
                {
                    LogError("extract failed.");
                    return false;
                }
                res.clear();
                for(size_t i = 0; i < wordweights.size(); i++)
                {
                    const string& word = wordweights[i].first;
                    res.push_back(make_pair(_hasher(word.c_str(), word.size(), 0), wordweights[i].second));
                }

                return true;
            }

            bool make(const string& text, size_t topN, uint64_t& v64) const
            {
                vector<pair<uint64_t, double> > hashvalues;
                if(!make(text, topN, hashvalues))
                {
                    return false;
                }
                vector<double> weights(BITS_LENGTH, 0.0);
                const uint64_t u64_1(1);
                for(size_t i = 0; i < hashvalues.size(); i++)
                {
                    for(size_t j = 0; j < BITS_LENGTH; j++)
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
                for(size_t j = 0; j < BITS_LENGTH; j++)
                {
                    if(weights[j] > 0.0)
                    {
                        v64 |= (u64_1 << j);
                    }
                }
                
                return true;
            }
            
            static bool isEqual(uint64_t lhs, uint64_t rhs, unsigned short n = 3)
            {
                unsigned short cnt = 0;
                lhs ^= rhs;
                while(lhs && cnt <= n)
                {
                    lhs &= lhs - 1;
                    cnt++;
                }
                if(cnt <= n)
                {
                    return true;
                }
                return false;
            }

            static void toBinaryString(uint64_t req, string& res)
            {
                res.resize(64);
                for(signed i = 63; i >= 0; i--)
                {
                    req & 1 ? res[i] = '1' : res[i] = '0';
                    req >>= 1;
                }
            }

            static uint64_t binaryStringToUint64(const string& bin)
            {
                uint64_t res = 0;
                for(size_t i = 0; i < bin.size(); i++)
                {
                    res <<= 1;
                    if(bin[i] == '1')
                    {
                        res += 1;
                    }
                }
                return res;
            }

    };
}

#endif


