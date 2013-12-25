#include <iostream>
#include <fstream>
#include "CppJieba/Limonp/io_functs.hpp"
#include "CppJieba/MixSegment.hpp"

using namespace Limonp;
using namespace CppJieba;

bool cut(ISegment* segHandle, const string& doc, vector<string>& words)
{
    return segHandle->cut(doc, words);
}


int main(int argc, char** argv)
{
    if(argc < 2)
    {
        fprintf(stderr, "usage: %s <filename>", argv[0]);
        return EXIT_FAILURE;
    }
    string doc;
    loadFile2Str(argv[0], doc);
    
    return EXIT_SUCCESS;
}
