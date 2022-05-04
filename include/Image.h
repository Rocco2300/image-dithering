#pragma once

#include <stdint.h>

#pragma pack(push, 1)

typedef struct 
{
    uint16_t header;
    uint32_t size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t startingOffset;

} ImageHeader;

typedef struct
{
    uint32_t headerSize;
    uint32_t width;
    uint32_t height;
    uint16_t colorPlanes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t imageSize;
    uint32_t horizontalResolution;
    uint32_t verticalResolution;
    uint32_t colorNumber;
    uint32_t importantColors;

} DIBHeader;

typedef struct
{
    uint8_t b;
    uint8_t g;
    uint8_t r;

} Pixel;

#pragma pack(pop)

typedef struct
{
    ImageHeader* header;
    DIBHeader* dibHeader;
    Pixel* pixels;

} Image;

Image* create_empty_image();
Image* load_image(const char* path);
void destroy_image(Image* image);
void save_image(const char* path, Image* image);

Pixel* pixel_at(Image* image, int x, int y);