#include "convertor.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "../library/stb_image.h"

using namespace std;

uint8_t Convertor::toGray(uint8_t R, uint8_t G, uint8_t B) {
    return (R*299 + G*587 + B*114) / 1000;
}

char Convertor::toChar(uint8_t gray) {
    int index = (gray * (N - 1)) / 255;
    return RAMP[index];
}

Convertor::Convertor() {
    data=nullptr;
    width=0;
    height=0;
    channels=0;
    blockW=0;
    blockH=0;
    rows=0;
}

Convertor::Convertor(const string& inputPath) {
    path = inputPath;
    loadImage();
}


void Convertor::loadImage() {
    if (data != nullptr)
        stbi_image_free(data);

    data = stbi_load(
        path.c_str(),
        &width,
        &height,
        &channels,
        3
        );

    setRes();

    if (!data) {
        cout << "Failed to load image: " << "\n";
        return;
    }

    cout << "image width: " << width << endl
         << "image height: " << height << endl
         << "image channels: " << channels << endl;
}

void Convertor::pathChange(const string &input_path) {
    path = input_path;
    loadImage();
}

void Convertor::setRes(int new_cols) {
    if (new_cols < 0) {
        blockW = width / cols;
        blockH = blockW * 2;
        rows = height / blockH;
    }

    cols = new_cols;
    blockW = width / cols;
    blockH = blockW * 2;
    rows = height / blockH;
}

void Convertor::imageAscii() {
    if (!data) {
        cout << "data was loaded\n";
        return;
    }

    for (int row=0; row<rows; row++) {
        for (int col=0; col<cols; col++) {
            int sum=0;
            for (int dy=0; dy<blockH; dy++) {
                for (int dx=0; dx<blockW; dx++) {
                    int px = col * blockW + dx;
                    int py = row * blockH + dy;
                    if (px >= width || py >= height) continue;
                    int i = (py * width + px) * 3;
                    sum += toGray(data[i], data[i+1], data[i+2]);
                }
            }
            uint8_t avg = sum/(blockW * blockH);
            cout << toChar(avg);
        }
        cout << "\n";
    }
}

Convertor::~Convertor() {
    stbi_image_free(data);
}

