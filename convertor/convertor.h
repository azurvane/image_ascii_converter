//
// Created by azurvane on 18/04/26.
//

#ifndef CONVERTOR_H
#define CONVERTOR_H

#include <iostream>
#include "../library/stb_image.h"

using namespace std;


class convertor {
private:
    const string RAMP = "@#S%?*+;:,. ";
    const int N = RAMP.size();
    int width, height, channels;
    unsigned char* data;
    uint8_t toGray(uint8_t R, uint8_t G, uint8_t B);
    char toChar(uint8_t gray);
    void loadImage(const string& path);


public:
    convertor();
    convertor(const string& path);
    void image_ascii();

    ~convertor();
};



#endif //CONVERTOR_H
