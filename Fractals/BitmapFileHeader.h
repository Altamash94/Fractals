#pragma once
#ifndef _BITMAPFILEHEADER_H_
#define _BITMAPFILEHEADER_H_

#include <inttypes.h>
using namespace std;

#pragma pack(2)
namespace Advance {
    struct BitmapFileHeader {
        char header[2]{ 'B', 'M' };
        int32_t fileSize{ 0 };
        int32_t reserved{ 0 };
        int32_t dataOffset{ 0 };
    };
}

#endif