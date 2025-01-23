#include "Color.h"
//Color24
bool Color24::operator<(const Color24& other) const {
    return other.red < red;
}
bool Color24::operator!=(const Color24& other) const {
    return other.red != red && other.blue != blue && other.green != green;
}
bool Color24::operator==(const Color24& other) const {
    return other.red == red && other.blue == blue && other.green == green;
}
std::ostream& operator << (std::ostream& out, const Color24& color) {
    out << "(" << (unsigned)color.red << ", " << (unsigned)color.green << ", " << (unsigned)color.blue << ", " << (unsigned)255 << ")";
    return out;
}

//Color32
bool Color32::operator<(const Color32& other) const {
    return other.red < red;
}
bool Color32::operator!=(const Color32& other) const {
    return other.red != red && other.blue != blue && other.green != green && other.alpha != alpha;
}
bool Color32::operator==(const Color32& other) const {
    return other.red == red && other.blue == blue && other.green == green && other.alpha == alpha;
}
std::ostream& operator << (std::ostream& out, const Color32& color) {
    out << "(" << (unsigned)color.red << ", " << (unsigned)color.green << ", " << (unsigned)color.blue << ", " << (unsigned)color.alpha << ")";
    return out;
}