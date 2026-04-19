#ifndef CONVERTOR_H
#define CONVERTOR_H

#include <iostream>

using namespace std;


class Convertor {
    const string RAMP = "@#S%?*+;:,. ";
    const int N = RAMP.size();
    int width, height, channels;
    unsigned char* data;
    string path;
    int cols = 176;
    int blockW, blockH, rows;
    std::vector<uint8_t> gray;


    uint8_t toGray(uint8_t R, uint8_t G, uint8_t B);
    char toChar(uint8_t gray);
    void ToGrayVector();
    pair<float, float> sobelAt(int px, int py);
    char directionChar(float angle);

    void loadImage();


public:
    Convertor();
    Convertor(const string& inputPath);
    void pathChange(const string& input_path);
    void setRes(int new_cols=-1);
    void imageAscii();

    ~Convertor();
};



#endif //CONVERTOR_H
