#include "convertor.h"
#include <iostream>
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
}

Convertor::Convertor(const string& inputPath) {
    data=nullptr;
    width=0;
    height=0;
    channels=0;
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

    if (!data) {
        cout << "Failed to load image: " << "\n";
        return;
    }

    cout << "image width: " << width << endl
         << "image height: " << height << endl
         << "image channels: " << channels << endl;
}

void Convertor::pathChange(const string &inputPath) {
    path = inputPath;
    loadImage();
}


void Convertor::imageAscii() {
    if (!data) {
        cout << "data was loaded\n";
        return;
    }

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

Convertor::~Convertor() {
    stbi_image_free(data);
}

