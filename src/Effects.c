#include "Effects.h"

#include <math.h>

void quantize_pixel(Pixel* pixel, int factor)
{
    pixel->r = round(factor * pixel->r / 255.f) * (255.f / factor);
    pixel->g = round(factor * pixel->g / 255.f) * (255.f / factor);
    pixel->b = round(factor * pixel->b / 255.f) * (255.f / factor);
}

void grayscale(Image* image)
{
    int w = image->dibHeader->width;
    int h = image->dibHeader->height;

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            Pixel* pixel = pixel_at(image, x, y);

            int value = (pixel->r + pixel->g + pixel->b) / 3;
            pixel->r = value;
            pixel->g = value;
            pixel->b = value;
        }
    }
}

void quantize(Image* image, int factor)
{
    int w = image->dibHeader->width;
    int h = image->dibHeader->height;

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            quantize_pixel(pixel_at(image, x, y), factor);
        }
    }
}