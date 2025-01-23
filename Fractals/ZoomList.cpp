#include "ZoomList.h"
#include <iostream>

ZoomList::ZoomList(int width, int height) :
    m_width(width),
    m_height(height),
    m_transform(Mat<double>(3, 3)) {}

void ZoomList::add(Zoom zoom) {
    zooms.push_back(zoom);
}

void ZoomList::apply() {
    m_transform = Mat<double>(3, 3);
    Mat<double>zoom_transform(3, 3);
    for (Zoom zoom : zooms) {
        zoom_transform.data[0] = zoom.scale;
        zoom_transform.data[4] = zoom.scale;
        zoom_transform.data[2] = (zoom.translate.x * 2.0 ) / m_width;
        zoom_transform.data[5] = (zoom.translate.y * 2.0) / m_height;
        m_transform = zoom_transform * m_transform;
    }
}

std::pair<double, double> ZoomList::transform(int x, int y) {
    return std::pair<double, double>(0, 0);
}