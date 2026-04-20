#ifndef CONVERTOR_H
#define CONVERTOR_H

#include <iostream>

using namespace std;


class Convertor {
    // const string RAMP = "@#S%?*+;:,. ";
    const string RAMP = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'. ";
    const int N = RAMP.size();
    int width, height, channels;
    unsigned char* data;
    string path;
    int cols = 176;
    int blockW, blockH, rows;
    vector<uint8_t> gray;


    uint8_t toGray(uint8_t R, uint8_t G, uint8_t B);
    char toChar(uint8_t gray);
    void ToGrayVector();
    pair<float, float> sobelAt(int px, int py);
    static char directionChar(float angle);

    void loadImage();


public:
    Convertor();
    Convertor(const string& inputPath);
    void pathChange(const string& input_path);
    void setRes(int new_cols=-1);

    uint8_t avgGray(int row, int col);

    vector<float> calErrorBuf(vector<float> errorBuf, float adjusted, int row, int col);

    void imageAscii();

    ~Convertor();
};



#endif //CONVERTOR_H
