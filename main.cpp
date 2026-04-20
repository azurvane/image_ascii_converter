#include <iostream>
#define STB_IMAGE_IMPLEMENTATION  // tells stb to include the actual code
#include "convertor/convertor.h"

using namespace std;



int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "image path is not provided\n";
        return 1;
    }
    Convertor convertor(argv[1]);
    convertor.imageAscii();
}