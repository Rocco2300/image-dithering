#include "Image.h"

#include <stdio.h>
#include <stdlib.h>

void destroy_image(Image* image)
{
    if (image == NULL)
        return;

    if (image->header != NULL)
        free(image->header);

    if (image->dibHeader != NULL)
        free(image->dibHeader);
    
    if (image->pixels != NULL)
        free(image->pixels);
}

Image* create_empty_image()
{
    Image* image;
    image = malloc(sizeof(Image));

    if (image == NULL)
        return NULL;
    
    image->header = malloc(sizeof(ImageHeader));
    if (image->header == NULL)
    {
        destroy_image(image);
        return NULL;
    }

    image->dibHeader = malloc(sizeof(DIBHeader));
    if (image->dibHeader == NULL)
    {
        destroy_image(image);
        return NULL;
    }

    return image;
}

Image* load_image(const char* path)
{
    Image* image = create_empty_image();

    if (image == NULL)
        return NULL;

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

    return image;
}

void save_image(const char* path, Image* image)
{
    FILE* file;
    file = fopen(path, "wb");

    int width = image->dibHeader->width;
    int height = image->dibHeader->height;

    int padding;
    if ((sizeof(Pixel) * width) % 4 == 0)
        padding = 0;
    else
        padding = 4 - (sizeof(Pixel) * width) % 4;

    fwrite(image->header, 14, 1, file);
    fwrite(image->dibHeader, 40, 1, file);

    Pixel* pixel = calloc(1, sizeof(Pixel));
    for (int i = height - 1; i >= 0; i--)
    {
        int offset = i * width;
        fwrite(image->pixels + offset, sizeof(Pixel) * width, 1, file);
        fwrite(pixel, sizeof(Pixel), padding, file);
    }

    fclose(file);
}

Pixel* pixel_at(Image* image, int x, int y)
{
    int width = image->dibHeader->width;
    int height = image->dibHeader->height;

    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        fprintf(stderr, "Pixel is out of bounds!");
        
        return NULL;
    }

    int idx = y * width + x;
    return &image->pixels[idx];
}