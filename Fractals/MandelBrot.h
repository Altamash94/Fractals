#pragma once
#include<math.h>
#include<map>
#include<set>
#include<vector>
#include<iostream>
#include<memory>
#include "types.h"


template<typename T>
class Mandelbrot {
private:
    int m_width{};
    int m_height{};
public:
    std::map<std::string, std::set<float>> values;
    std::map<std::string, std::set<Vec2<double>>> NDCs;
    int m_totalHistogram{ 0 };
    const int MAX_ITERATIONS = 1000;
    std::unique_ptr<int[]> m_histogram{};
    std::unique_ptr<int[]> m_iteration{};
    Mandelbrot(int width, int height);
    void PrepareData();
    int GetIteration(Vec2<double> NDC);
    T GetColor(Vec2<int> pos);
    void Print();
    void Print(std::map<std::string, std::set<float>> values);
    Mat<double> m_transform;
};