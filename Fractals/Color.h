#pragma once
#include <cstdint>
#include <ostream>
#include <iostream>
#include <memory>

struct Color24 {
    uint8_t blue{ (uint8_t)255 };
    uint8_t green{ (uint8_t)255 };
    uint8_t red{ (uint8_t)255 };
    Color24(uint8_t r, uint8_t g, uint8_t b) : red(r), blue(b), green(g) {}
    Color24(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : red(r), blue(b), green(g) {}
    Color24(uint8_t c) : red(c), blue(c), green(c) {}
    Color24(uint8_t c, uint8_t a) : red(c), blue(c), green(c) {}
    Color24() : red(255), blue(255), green(255) {}
    uint8_t GetAlpha() { return 255; }
    void SetAlpha(uint8_t a) {}
    friend std::ostream& operator << (std::ostream& out, const Color24& color);
    bool operator<(const Color24& other) const;
    bool operator!=(const Color24& other) const;
    bool operator==(const Color24& other) const;

};

struct Color32 {

    uint8_t blue{ (uint8_t)255 };
    uint8_t green{ (uint8_t)255 };
    uint8_t red{ (uint8_t)255 };
    uint8_t alpha = 0;
    Color32(uint8_t r, uint8_t g, uint8_t b) : red(r), blue(b), green(g), alpha(0) {}
    Color32(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : red(r), blue(b), green(g), alpha(a) {}
    Color32(uint8_t c) : red(c), blue(c), green(c), alpha(0) {}
    Color32(uint8_t c, uint8_t a) : red(c), blue(c), green(c), alpha(a) {}
    Color32() : red(255), blue(255), green(255), alpha(0) {}
    uint8_t GetAlpha() const { return alpha; }
    void SetAlpha(uint8_t a) { alpha = a; }
    friend std::ostream& operator << (std::ostream& out, const Color32& color);
    bool operator<(const Color32& other) const;
    bool operator!=(const Color32& other) const;
    bool operator==(const Color32& other) const;
};