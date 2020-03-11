#ifndef SIMHASH_SIMHASHER_HPP
#define SIMHASH_SIMHASHER_HPP

#include "cppjieba/KeywordExtractor.hpp"
#include "jenkins.h"

namespace simhash
{
    using namespace cppjieba;
    class Simhasher
    {
        private:
            enum{BITS_LENGTH = 64};
            jenkins _hasher;
            KeywordExtractor _extractor;
        public:
            Simhasher(const string& dictPath, const string& modelPath, const string& idfPath, const string& stopWords): _extractor(dictPath, modelPath, idfPath, stopWords)
            {}
            ~Simhasher(){};

            bool extract(const string& text, vector<pair<string,double> > & res, size_t topN) const
            {
                return _extractor.Extract(text, res, topN);
            }
            bool make(const string& text, size_t topN, vector<pair<uint64_t, double> >& res) const
            {
                vector<pair<string, double> > wordweights;
                if(!extract(text, wordweights, topN))
                {
                    XLOG(ERROR) << "extract failed";
                    return false;
                }
                res.resize(wordweights.size());
                for(size_t i = 0; i < res.size(); i++)
                {
                    res[i].first = _hasher(wordweights[i].first.c_str(), wordweights[i].first.size(), 0);
                    res[i].second = wordweights[i].second;
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
                        weights [j] += (((u64_1 << j) & hashvalues[i].first) ? 1: -1) * hashvalues[i].second;
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
          
            /**
             * @brief
             * Directly calculate weighted hash of pre-defined keywords.
             */ 
            static uint64_t make_from_predefined_keywords(const std::vector< std::pair<std::string, double> >& keywords) {
                uint64_t v64 = 0;
                std::vector< std::pair<uint64_t, double> > hashvalues;
                jenkins _tmp_hasher;

                hashvalues.resize(keywords.size());
                for (int32_t i = 0; i < keywords.size(); ++i) {
                    hashvalues[i].first = _tmp_hasher(keywords[i].first.c_str(), keywords[i].first.size(), 0);
                    hashvalues[i].second = keywords[i].second;
                }

                vector<double> weights(BITS_LENGTH, 0.0);
                const uint64_t u64_1(1);
                for(size_t i = 0; i < hashvalues.size(); i++)
                {
                    for(size_t j = 0; j < BITS_LENGTH; j++)
                    {
                        weights [j] += (((u64_1 << j) & hashvalues[i].first) ? 1: -1) * hashvalues[i].second;
                    }
                }

                for(size_t j = 0; j < BITS_LENGTH; j++)
                {
                    if(weights[j] > 0.0)
                    {
                        v64 |= (u64_1 << j);
                    }
                }

                return v64;
            }

            static bool isEqual(uint64_t lhs, uint64_t rhs, unsigned short n = 3)
            {
                unsigned short cnt = 0;
                lhs ^= rhs;
#if 	defined(__GNUC__) ||  defined(__clang__)
                cnt = __builtin_popcountll(lhs);
#else
                /*
                 * FIXME: There are actually also builtin_popcount-like functions
                 * in other compilers..
                 * Anyway..Here, we just roll back to look-up table (8bits).
                 */
                static const int pop_lut[256] = {
                		0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
                		1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
                		1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
                		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
                		1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
                		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
                		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
                		3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
                		1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
                		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
                		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
                		3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
                		2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
                		3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
                		3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
                		4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
                };

                while(lhs && cnt <= n)
                {
                	cnt += pop_lut[lhs & 0xff];
                	lhs >>= 8;
                }
#endif
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


