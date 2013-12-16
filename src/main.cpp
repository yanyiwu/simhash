#include <iostream>
#include <fstream>
#include "CppJieba/Limonp/io_functs.hpp"

using namespace Limonp;


bool cut

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
