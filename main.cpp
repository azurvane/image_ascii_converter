#include <iostream>
#define STB_IMAGE_IMPLEMENTATION  // tells stb to include the actual code
#include "convertor/convertor.h"

using namespace std;



int main(int argc, char* argv[]) {
    Convertor convertor(argv[1]);
    convertor.imageAscii();
}