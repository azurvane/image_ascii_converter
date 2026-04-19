//
// Created by azurvane on 18/04/26.
//

#ifndef CONVERTOR_H
#define CONVERTOR_H

#include <iostream>
#include "../library/stb_image.h"

using namespace std;


class Convertor {
private:
    const string RAMP = "@#S%?*+;:,. ";
    const int N = RAMP.size();
    int width, height, channels;
    unsigned char* data;
    string path;


    uint8_t toGray(uint8_t R, uint8_t G, uint8_t B);
    char toChar(uint8_t gray);
    void loadImage();


public:
    Convertor();
    Convertor(const string& inputPath);
    void pathChange(const string& inputPath);
    void imageAscii();

    ~Convertor();
};



#endif //CONVERTOR_H
