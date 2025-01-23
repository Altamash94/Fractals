#pragma once

#include <inttypes.h>
#include <string>
#include <memory>
#include <fstream>
#include <iostream>
#include <math.h>
#include <complex>
#include <map>
#include <set>
#include "types.h"
#include "TestInfo.h"

using namespace std;


template<typename T>
class Bitmap {
private:
    std::unique_ptr<T[]> m_PtrPixels{ nullptr };

public:
    map<string, set<float>> values;
    map<string, set<T>> colors;
    map<string, set<TestInfo>> values_Positions;
    Bitmap(int width, int height);
    int32_t m_width{ 0 };
    int32_t m_height{ 0 };
    void setPixel(Vec2<int> pos, T& color);
    void setPixel(std::unique_ptr<T[]> tempPtr, Vec2<int> pos, T& color);
    bool write(std::string filename);
    Mat<double> m_transform;

    ~Bitmap();
    void DrawCircle(Vec2<int> center, int radius, T& color, Mat<double> transform);
    void DrawFractal(Mat<double> transform);
    T Blend(T color1, T color2);
    T AddColor(T, float, T, float);
    void Print(map<string, set<float>> values);
    void PrintPositions(map<string, set<TestInfo>> values_Positions);

};