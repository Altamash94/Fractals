#include <iostream>
#include <math.h>
#include <sstream>
#include "BitmapFileHeader.h"
#include "BitmapInfoHeader.h"
#include "Mandelbrot.h"
#include "Bitmap.h"

template class Bitmap<Color24>;
template class Bitmap<Color32>;


template <typename T>
Bitmap<T>::Bitmap(int width, int height) :
    m_width(width),
    m_height(height),
    m_PtrPixels(new T[width * height]{ T(0,0,0,0) }),
    m_transform(Mat<double>(3, 3))
{
}

template <typename T>
void Bitmap<T>::setPixel(Vec2<int> pos, T& color)
{
    m_PtrPixels[pos.y * m_width + pos.x] = color;
}

template <typename T>
void Bitmap<T>::setPixel(std::unique_ptr<T[]> tempPtr, Vec2<int> pos, T& color) {
    tempPtr[pos.y * m_width + pos.x] = color;
}

template <typename T>
bool Bitmap<T>::write(std::string filename) {
    Advance::BitmapFileHeader fileHeader;
    Advance::BitmapInfoHeader infoHeader;

    fileHeader.fileSize = sizeof(Advance::BitmapFileHeader) + sizeof(Advance::BitmapInfoHeader) + (sizeof(T) * m_width + m_height);
    fileHeader.dataOffset = sizeof(Advance::BitmapFileHeader) + sizeof(Advance::BitmapInfoHeader);
    infoHeader.width = m_width;
    infoHeader.height = m_height;
    infoHeader.bitsPerPixel = sizeof(T) * 8;

    ofstream file;
    file.open(filename, ios::out | ios::binary);

    file.write((char*)&fileHeader, sizeof(fileHeader));
    file.write((char*)&infoHeader, sizeof(infoHeader));
    file.write((char*)m_PtrPixels.get(), (sizeof(T) * m_width * m_height));
    file.close();

    return true;
}

template <typename T>
Bitmap<T>::~Bitmap() {
}

template <typename T>
void Bitmap<T>::DrawCircle(Vec2<int> center, int radius, T& color, Mat<double> transform) { 
    m_transform = transform;
    center = center.Transform(m_transform, m_width, m_height);
    radius = (int)(radius * transform.data[0]);

    for (int i = 0; i < m_height; i++) {
        for (int j = 0; j < m_width; j++) {
            double r = sqrt(pow(j - center.x, 2) + pow(i - center.y, 2));
            if (r < radius) {
                T colorB = Blend(m_PtrPixels[i * m_width + j], color);
                setPixel(Vec2<int>(j, i), colorB);
            }
        }
    }

}

template <typename T>
void Bitmap<T>::DrawFractal(Mat<double> transform) {

    Mandelbrot<T> mandelbrot(m_width, m_height);
    mandelbrot.m_transform = transform;
    mandelbrot.PrepareData();
    mandelbrot.Print(mandelbrot.values);

    for (int i = 0; i < m_height; i++) {
        for (int j = 0; j < m_width; j++) {
            T color = mandelbrot.GetColor(Vec2<int>(j, i));
            setPixel(Vec2<int>(j, i), color);
        }
    }
}

template <typename T>
T Bitmap<T>::AddColor(T destinationColor, float destinationFactor, T soureColor, float SourceFactor) {
    int dR = destinationColor.red;
    int dG = destinationColor.green;
    int dB = destinationColor.blue;
    int dA = destinationColor.GetAlpha();

    int sR = soureColor.red;
    int sG = soureColor.green;
    int sB = soureColor.blue;
    int sA = soureColor.GetAlpha();

    int rR = (int)(dR * destinationFactor + sR * SourceFactor);
    int rG = (int)(dG * destinationFactor + sG * SourceFactor);
    int rB = (int)(dB * destinationFactor + sB * SourceFactor);
    int rA = (int)(dA * destinationFactor + sA * SourceFactor);


    return T(rR, rG, rB, rA);
}

template <typename T>
T Bitmap<T>::Blend(T destinationColor, T sourceColor) {
    float sourceAlpha = (unsigned)sourceColor.GetAlpha() / 255.0f;



    float SourceFactor = sourceAlpha;
    float DestinationFactor = 1.0f - sourceAlpha;

    T result = AddColor(destinationColor, DestinationFactor, sourceColor, SourceFactor);

    return result;
}

template<typename T>
void Bitmap<T>::Print(map<string, set<float>> values) {

    for (map<string, set<float>>::iterator it = values.begin(); it != values.end(); it++) {
        std::cout << it->first << "(";
        for (set<float>::iterator vi = it->second.begin(); vi != it->second.end(); vi++) {
            std::cout << *vi << ",";
        }
        std::cout << ")" << endl;
    }

    std::cout << endl;
}

template<typename T>
void Bitmap<T>::PrintPositions(map<string, set<TestInfo>> values_Positions)
{
    std::ostream& os = std::cout;
    std::stringstream ss;
    for (map<string, set<TestInfo>>::iterator it = values_Positions.begin(); it != values_Positions.end(); it++) {
        os << it->first << endl << "(";
        for (set<TestInfo>::iterator vi = it->second.begin(); vi != it->second.end(); vi++) {
            TestInfo t = *vi;
            os << t << endl;
        }
        os << ")" << endl;
    }
    ss << os.rdbuf();
    std::cout << ss.str() << endl << endl;;
}