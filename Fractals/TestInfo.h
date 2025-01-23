#include "types.h"

class TestInfo {
public:
    Vec2<int> originalPos;
    Vec2<double> normalized;
    Vec2<int> transformedPos;
    Mat<double> m_transform;
    double xNormalizeFactor, xCoOrdinateFactor, yNormalizeFactor, yCoOrdinateFactor;
    TestInfo(
        Vec2<int> originalPos, double xNormalizeFactor, double yNormalizeFactor,
        Vec2<double> normalized,
        Vec2<int> transformedPos, double xCoOrdinateFactor, double yCoOrdinateFactor,
        Mat<double> m_transform) :
        originalPos(originalPos),
        xNormalizeFactor(xNormalizeFactor),
        yNormalizeFactor(yNormalizeFactor),
        normalized(normalized),
        transformedPos(transformedPos),
        xCoOrdinateFactor(xCoOrdinateFactor),
        yCoOrdinateFactor(yCoOrdinateFactor),
        m_transform(m_transform)
    {

    }

    bool operator!=(const TestInfo& other) const {
        return other.originalPos.x != originalPos.x && other.originalPos.y != originalPos.y;
    }

    bool operator<(const TestInfo& other) const {
        return originalPos < other.originalPos;
    }

    friend std::ostream& operator << (std::ostream& out, const TestInfo& testInfo)
    {
        //out << "Transform Mat" << std::endl << testInfo.m_transform;
        
        out << "Origianl Pos\t";
        out << "(" << testInfo.originalPos.x << ", " << testInfo.originalPos.y << ")\t";
        out << testInfo.xNormalizeFactor << ", " << testInfo.yNormalizeFactor << std::endl;

        out << "Normalized\t" << testInfo.normalized << std::endl;
        
        out << "transformed Pos\t";
        out << "(" << testInfo.transformedPos.x << ", " << testInfo.transformedPos.y << ")\t";
        out << testInfo.xCoOrdinateFactor << ", " << testInfo.yCoOrdinateFactor << std::endl;
        return out;
    }

};