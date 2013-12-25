#include <iostream>
#include <fstream>
//#include "CppJieba/KeywordExtractor.hpp"
#include "Simhash.hpp"


//const char * const FILE_PATH = "";

using namespace SimhashSpace;

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        fprintf(stderr, "usage: %s <filename>", argv[0]);
        return EXIT_FAILURE;
    }
    Simhash sh("dict1", "dict2");
    //string doc((istreambuf_iterator<char>(agrv[])));
    //loadFile2Str(argv[0], doc);
    
    return EXIT_SUCCESS;
}
