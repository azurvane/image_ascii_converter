#include "convertor.h"
#include <iostream>
#include "../library/stb_image.h"

using namespace std;

uint8_t convertor::toGray(uint8_t R, uint8_t G, uint8_t B) {
    return (R*299 + G*587 + B*114) / 1000;
}

char convertor::toChar(uint8_t gray) {
    int index = (gray * (N - 1)) / 255;
    return RAMP[index];
}

convertor::convertor() {
    data=nullptr;
    width=0;
    height=0;
    channels=0;
}

convertor::convertor(const string& path) {
    data=nullptr;
    width=0;
    height=0;
    channels=0;
    loadImage(path);
}


void convertor::loadImage(const string& path) {
    if (data != nullptr)
        stbi_image_free(data);

    data = stbi_load(
        path.c_str(),
        &width,
        &height,
        &channels,
        3
        );

    if (!data) {
        cout << "Failed to load image: " << "\n";
        return;
    }

    cout << "image width: " << width << endl
         << "image height: " << height << endl
         << "image channels: " << channels << endl;
}


void convertor::image_ascii() {
    for (int row=0; row<height; row++) {
        for (int col=0; col<width; col++) {
            int i = (row * width + col) * 3;
            uint8_t R = data[i], G = data[i+1], B = data[i+2];
            uint8_t gray = toGray(R, G, B);
            cout << toChar(gray);
        }
        cout << "\n";
    }
}

convertor::~convertor() {
    stbi_image_free(data);
}

