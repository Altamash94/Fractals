#pragma once
#include <vector>
#include <utility>
#include "types.h"


struct Zoom {
    Vec2<int> translate{ Vec2<int>(0, 0) };
    double scale{ 1.0 };
    Zoom(Vec2<int> translate, double scale) : translate(translate), scale(scale) {}
};

class ZoomList {
private:
    int m_width{ 0 }, m_height{ 0 };
    std::vector<Zoom> zooms;
public:
    Mat<double> m_transform{ Mat<double>(3, 3) };
    double m_scale{ 1.0 };
    ZoomList(int width, int height);
    void add(Zoom zoom);
    void apply();
    std::pair<double, double> transform(int x, int y);

};