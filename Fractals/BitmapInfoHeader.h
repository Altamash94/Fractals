#pragma once
#ifndef _BITMAPINFOHEADER_H_
#define _BITMAPINFOHEADER_H_

#include <inttypes.h>
using namespace std;

#pragma pack(2)
namespace Advance {
    struct BitmapInfoHeader {
        int32_t headerSize{ 40 };
        int32_t width{ 0 };
        int32_t height{ 0 };
        int16_t plane{ 1 };
        int16_t bitsPerPixel{ 24 };
        int32_t compression{ 0 };
        int32_t dataSize{ 0 };
        int32_t horizontalResolution{ 2400 };
        int32_t verticalResolution{ 2400 };
        int32_t colors{ 0 };
        int32_t importantColors{ 0 };
    };
}

#endif