#include <stdio.h>
#include <stdlib.h>
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

Image* create_image()
{
    Image* image;
    image = malloc(sizeof(Image));

    if (image == NULL)
        return NULL;
    
    image->header = malloc(sizeof(ImageHeader));
    image->dibHeader = malloc(sizeof(DIBHeader));

    return image;
}

void load_image(const char* path, Image* image)
{
    FILE* file;
    file = fopen(path, "rb");

    fread(image->header, 14, 1, file);
    fread(image->dibHeader, 40, 1, file);

    int width = image->dibHeader->width;
    int height = image->dibHeader->height;
    int size = width * height;
    image->pixels = malloc(sizeof(Pixel) * size);

    int padding;
    if ((sizeof(Pixel) * width) % 4 == 0)
        padding = 0;
    else
        padding = 4 - (sizeof(Pixel) * width) % 4;

    for (int i = height - 1; i >= 0; i--)
    {
        int offset = i * width;
        fread(image->pixels + offset, sizeof(Pixel) * width, 1, file);
        fseek(file, sizeof(Pixel) * padding, SEEK_CUR);
    }

    fclose(file);
}

int main()
{
    Image* image = create_image();
    load_image("test.bmp", image);

    int w = image->dibHeader->width;
    int h = image->dibHeader->height;

    printf("%d %d\n", w, h);

    printf("%d %d %d", image->pixels[0].r, image->pixels[0].g, image->pixels[0].b);
    return 0;
}