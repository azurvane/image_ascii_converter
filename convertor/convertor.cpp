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
    float a = abs(deg);

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

uint8_t Convertor::avgGray(int row, int col) {
    int sum=0;
    int count=0;
    for (int dy=0; dy<blockH; dy++) {
        for (int dx=0; dx<blockW; dx++) {
            int px = col * blockW + dx;
            int py = row * blockH + dy;
            if (px >= width || py >= height) continue;
            int i = py * width + px;
            sum += gray[i];
            count++;
        }
    }
    return sum/count;
}

vector<float> Convertor::calErrorBuf(vector<float> errorBuf, float adjusted, int row, int col) {
    int charIndex = static_cast<uint8_t>(adjusted) * (N - 1) / 255;
    int actualBrightness = (charIndex * 255) / (N - 1);
    float error = adjusted - static_cast<float>(actualBrightness);

    if (col + 1 < cols)
        errorBuf[row * cols + (col+1)] += error * 7.0f / 16.0f;
    if (row + 1 < rows) {
        if (col - 1 >= 0)
            errorBuf[(row+1) * cols + (col-1)] += error * 3.0f / 16.0f;
        errorBuf[(row+1) * cols + col] += error * 5.0f / 16.0f;
        if (col + 1 < cols)
            errorBuf[(row+1) * cols + (col+1)] += error * 1.0f / 16.0f;
    }

    return errorBuf;
}

void Convertor::imageAscii() {
    if (!data) {
        cout << "data was loaded\n";
        return;
    }

    float threshold = 50.0f;
    vector errorBuf(rows * cols, 0.0f);

    for (int row=0; row<rows; row++) {
        for (int col=0; col<cols; col++) {

            uint8_t avg = avgGray(row, col);

            float adjusted = static_cast<float>(avg) + errorBuf[row * cols + col];
            adjusted = clamp(adjusted, 0.0f, 255.0f);

            int cx = col * blockW + blockW / 2;
            int cy = row * blockH + blockH / 2;
            auto [gx, gy] = sobelAt(cx, cy);
            float magnitude = sqrt(gx*gx + gy*gy);

            if (magnitude > threshold) {
                float angle = atan2(gy, gx);
                cout << directionChar(angle);
            }
            else {
                cout << toChar(static_cast<uint8_t>(adjusted));
                errorBuf = calErrorBuf(errorBuf, adjusted, row, col);
            }
        }
        cout << "\n";
    }
}

Convertor::~Convertor() {
    stbi_image_free(data);
}

