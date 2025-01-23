#include <iostream>
#include "Bitmap.h"
#include "types.h"
#include "ZoomList.h"



void drawFractal(Bitmap<Color32>& bitmap, Mat<double> fromTransform, Mat<double> toTransform, int n) {
    int N = 100;
	double deltaScale = (toTransform.data[0] - fromTransform.data[0]) / N;
	double deltaTranslateX = (toTransform.data[2] - fromTransform.data[2]) / N;
	double deltaTranslateY = (toTransform.data[5] - fromTransform.data[5]) / N;
    for (int i = 0; i < N; i++) {
		Mat<double> transform(3, 3);
		transform.data[0] = fromTransform.data[0] + i * deltaScale;
		transform.data[4] = fromTransform.data[4] + i * deltaScale;
		transform.data[2] = fromTransform.data[2] + i * deltaTranslateX;
		transform.data[5] = fromTransform.data[5] + i * deltaTranslateY;
		bitmap.DrawFractal(transform);
        bitmap.write("test_" + std::to_string(n++) + ".bmp");
		std::cout << n << std::endl;
    }
}

void drawFractal(Bitmap<Color32>& bitmap, vector<Zoom> zooms) {
    Mat<double> transform(3, 3);
    Mat<double> fromTransform(3, 3);
    int n = 0;
	int N = zooms.size();
	for (int i = 0; i < N; i++) {
		Zoom zoom = zooms[i];
		Mat<double> zoom_transform(3, 3);
		zoom_transform.data[0] = zoom.scale;
		zoom_transform.data[4] = zoom.scale;
		zoom_transform.data[2] = (zoom.translate.x * 2.0) / bitmap.m_width;
		zoom_transform.data[5] = (zoom.translate.y * 2.0) / bitmap.m_height;
		transform = zoom_transform * transform;
		drawFractal(bitmap, fromTransform, transform, n);
		n += 100;
		fromTransform = transform;

	}
}


int main() {
    
    
    
    const int WIDTH = 600, HEIGHT = 480;
    ZoomList zoomList(WIDTH, HEIGHT);
	std::vector<Zoom> zooms;
    zooms.push_back(Zoom(Vec2<int>(840, 0), 2.4));
    zooms.push_back(Zoom(Vec2<int>(300, 0), 4.0));
    zooms.push_back(Zoom(Vec2<int>(-200, 0), 2.0));
    zooms.push_back(Zoom(Vec2<int>(154, 227), 2.0));
    zooms.push_back(Zoom(Vec2<int>(9, 24), 4.0));
    zooms.push_back(Zoom(Vec2<int>(0, 0), 2.0));
    zooms.push_back(Zoom(Vec2<int>(0, 0), 2.0));
    zooms.push_back(Zoom(Vec2<int>(27, 12), 2.0));
    zooms.push_back(Zoom(Vec2<int>(0, 0), 2.0));
    zooms.push_back(Zoom(Vec2<int>(0, 0), 2.0));
    zooms.push_back(Zoom(Vec2<int>(0, 0), 2.0));
    zooms.push_back(Zoom(Vec2<int>(0, 0), 2.0));
    zooms.push_back(Zoom(Vec2<int>(0, 0), 2.0));
    zooms.push_back(Zoom(Vec2<int>(0, 369-240), 4.0));
    zooms.push_back(Zoom(Vec2<int>(0, 369-240), 2.0));
    zooms.push_back(Zoom(Vec2<int>(0, -240+138), 2.0));
    zooms.push_back(Zoom(Vec2<int>(0, 0), 4.0));
    zooms.push_back(Zoom(Vec2<int>(0, 0), 4.0));
    zooms.push_back(Zoom(Vec2<int>(270, 20), 4.0));
    zooms.push_back(Zoom(Vec2<int>(0, 0), 4.0));
    zooms.push_back(Zoom(Vec2<int>(13, -12), 4.0));
    zooms.push_back(Zoom(Vec2<int>(0, 0), 4.0));
    zooms.push_back(Zoom(Vec2<int>(14, 47), 4.0));
    zooms.push_back(Zoom(Vec2<int>(0, 0), 4.0));
    zooms.push_back(Zoom(Vec2<int>(50, 0), 4.0));
    zooms.push_back(Zoom(Vec2<int>(0, 0), 4.0));
    zooms.push_back(Zoom(Vec2<int>(0, 0), 4.0));
    zooms.push_back(Zoom(Vec2<int>(100, 0), 4.0));
    zooms.push_back(Zoom(Vec2<int>(0, 0), 4.0));

    for (Zoom zoom: zooms) {
		zoomList.add(zoom);
    }
	zoomList.apply();
	cout << "Zooms:\n" << zoomList.m_transform << endl;


    Color32 color(255, 0, 0, 127);
    Vec2<int> center(WIDTH / 2, HEIGHT / 2);
    int radius = 10;
    Bitmap<Color32> bitmap(WIDTH, HEIGHT);

    bitmap.DrawFractal(zoomList.m_transform);
    bitmap.DrawCircle(center, radius, color, Mat<double>(3, 3));
    bitmap.write("test.bmp");
	drawFractal(bitmap, zooms);

}