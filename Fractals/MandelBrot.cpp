#include "Mandelbrot.h"
#include <complex>

template class Mandelbrot<Color24>;
template class Mandelbrot<Color32>;

template<typename T>
Mandelbrot<T>::Mandelbrot(int width, int height) :
    m_width(width),
    m_height(height),
    m_histogram(new int[MAX_ITERATIONS] {0}),
    m_iteration(new int[width * height] {0}),
    m_transform(Mat<double>(3, 3)) {}

template<typename T>
int Mandelbrot<T>::GetIteration(Vec2<double> NDC) {
    int iterations = 0;
    std::complex<double> z = 0;
    std::complex<double> c(NDC.x, NDC.y);

    while (iterations < MAX_ITERATIONS) {
        z = z * z + c;
        if (abs(z) > 2)
            break;

        iterations++;
    }
    if (iterations != MAX_ITERATIONS)
        m_histogram[iterations]++;

    return iterations;
}

template<typename T>
void Mandelbrot<T>::PrepareData() {
    
    Mat<double> inverseTransform = m_transform.inverse();
    for (int i = 0; i < m_height; i++) {
        for (int j = 0; j < m_width; j++) {
            Vec2<double> NDC = Vec2<int>(j, i).Normalize(m_width, m_height);
            NDC = NDC.Transform(inverseTransform, m_width, m_height);
			int iteration = GetIteration(NDC);
            m_iteration[static_cast<size_t>(i) * m_width + j] = iteration;
        }
    }

    for (int i = 0; i < MAX_ITERATIONS; i++) {
        m_totalHistogram += m_histogram[i];
    }
}

template<typename T>
T Mandelbrot<T>::GetColor(Vec2<int> pos) {
    int iterations = m_iteration[static_cast<size_t>(pos.y) * m_width + pos.x];
    T color(0, 0, 0, 255);

    if (iterations != MAX_ITERATIONS) {
        double hue = 0.0;
        for (int i = 0; i < iterations; i++) {
            hue += (double)m_histogram[i] / (m_totalHistogram);
        }
        uint8_t v = (uint8_t)pow(255, hue);
        color = T(0, v, 0, 255);
    }

    return color;
}

template<typename T>
void Mandelbrot<T>::Print() {
    std::map<int, std::vector<int>> h;
    int sum = m_histogram[0];
    for(int i = 0; i < MAX_ITERATIONS; i++){
        h[m_histogram[i]].push_back(i);
        sum += m_histogram[i];
    }

    for (std::map<std::string, std::set<float>>::iterator it = values.begin(); it != values.end(); it++) {
        std::cout << it->first << "(";
        for (std::set<float>::iterator vi = it->second.begin(); vi != it->second.end(); vi++) {
            std::cout << *vi << ",";
        }
        std::cout << ")" << std::endl;
    }

    std::cout << std::endl;
}

template<typename T>
void Mandelbrot<T>::Print(std::map<std::string, std::set<float>> values) {

    for (std::map<std::string, std::set<float>>::iterator it = values.begin(); it != values.end(); it++) {
        std::cout << it->first << "(";
        for (std::set<float>::iterator vi = it->second.begin(); vi != it->second.end(); vi++) {
            std::cout << *vi << ",";
        }
        std::cout << ")" << std::endl;
    }

    std::cout << std::endl;
}