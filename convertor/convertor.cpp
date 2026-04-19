#include "convertor.h"
#include <iostream>
#include <numbers>
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

void Convertor::ToGrayVector() {
    for (int py=0; py<height; py++) {
        for (int px=0; px<width; px++) {
            int i = (py * width + px) * 3;
            gray[py * width + px] = toGray(data[i], data[i+1], data[i+2]);
        }
    }
}

pair<float, float> Convertor::sobelAt(int px, int py) {
    if (px <= 0 || px >= width-1 || py <= 0 || py >= height-1)
        return {0.0f, 0.0f};

    // neighbours by position
    float tl = gray[(py-1) * width + (px-1)];
    float tc = gray[(py-1) * width + (px  )];
    float tr = gray[(py-1) * width + (px+1)];
    float ml = gray[(py  ) * width + (px-1)];
    float mr = gray[(py  ) * width + (px+1)];
    float bl = gray[(py+1) * width + (px-1)];
    float bc = gray[(py+1) * width + (px  )];
    float br = gray[(py+1) * width + (px+1)];

    float gx = (tr + 2*mr + br) - (tl + 2*ml + bl);
    float gy = (bl + 2*bc + br) - (tl + 2*tc + tr);

    return make_pair(gx, gy);
}

char Convertor::directionChar(float angle) {
    float deg = angle * (180.0f / numbers::pi_v<float>);
    float a = std::abs(deg);

    if (a <= 22.5f || a >= 157.5f)  return '-';
    if (a >= 67.5f && a <= 112.5f)  return '|';
    if (deg > 22.5f && deg < 67.5f) return '/';
    return '\\';
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
    data = nullptr;
    loadImage();
}


void Convertor::loadImage() {
    if (data != nullptr) {
        stbi_image_free(data);
        data = nullptr; // Clear it so we don't try to free it again later
    }

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

    gray.resize(width * height);

    setRes();
    ToGrayVector();

    cout << "image width: " << width << endl
         << "image height: " << height << endl
         << "image channels: " << channels << endl;
}

void Convertor::pathChange(const string &input_path) {
    path = input_path;
    loadImage();
}

void Convertor::setRes(int new_cols) {
    if (new_cols > 0) {
        cols = new_cols;
    }

    blockW = width / cols;
    if (blockW == 0) blockW = 1;

    blockH = blockW * 2;
    rows = height / blockH;
}

void Convertor::imageAscii() {
    if (!data) {
        cout << "data was loaded\n";
        return;
    }
    float threshold = 50.0f;

    for (int row=0; row<rows; row++) {
        for (int col=0; col<cols; col++) {
            int sum=0;
            for (int dy=0; dy<blockH; dy++) {
                for (int dx=0; dx<blockW; dx++) {
                    int px = col * blockW + dx;
                    int py = row * blockH + dy;
                    if (px >= width || py >= height) continue;
                    int i = py * width + px;
                    sum += gray[i];
                }
            }
            uint8_t avg = sum/(blockW * blockH);
            int cx = col * blockW + blockW / 2;
            int cy = row * blockH + blockH / 2;
            auto [gx, gy] = sobelAt(cx, cy);
            float magnitude = std::sqrt(gx*gx + gy*gy);
            if (magnitude > threshold) {
                float angle = std::atan2(gy, gx);
                cout << directionChar(angle);
            }
            else {
                cout << toChar(avg);
            }
        }
        cout << "\n";
    }
}

Convertor::~Convertor() {
    stbi_image_free(data);
}

