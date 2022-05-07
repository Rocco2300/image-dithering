#include "Dither.h"

#include <math.h>

int mat4[4][4] = 
{
    {0, 8, 2, 10},
    {12, 4, 14, 6},
    {3, 11, 1, 9},
    {15, 7, 13, 5}
};


int mat8[8][8] = 
{
    {0, 32, 8, 40, 2, 34, 10, 42},
    {48, 16, 56, 24, 50, 18, 58, 26},
    {12, 44, 4, 36, 14, 46, 6, 38},
    {60, 28, 52, 20, 62, 30, 54, 22},
    {3, 35, 11, 43, 1, 33, 9, 41},
    {51, 19, 59, 27, 49, 17, 57, 25},
    {15, 47, 7, 39, 13, 45, 5, 37},
    {63, 31, 55, 23, 61, 29, 53, 21}
};

void dither_grayscale_4x4(Image* image)
{
    int w = image->dibHeader->width;
    int h = image->dibHeader->height;

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            Pixel* pixel = pixel_at(image, x, y);

            float normValue = pixel->r / 255.f;
            int newValue = (normValue < ((1.f/16) * (float)mat4[x % 4][y % 4])) ? 0 : 255;

            pixel->r = newValue;
            pixel->g = newValue;
            pixel->b = newValue;
        }
    }
}

void dither_grayscale_8x8(Image* image)
{
    int w = image->dibHeader->width;
    int h = image->dibHeader->height;

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            Pixel* pixel = pixel_at(image, x, y);

            float normValue = pixel->r / 255.f;
            int newValue = (normValue < ((1.f/64) * (float)mat8[x % 8][y % 8])) ? 0 : 255;

            pixel->r = newValue;
            pixel->g = newValue;
            pixel->b = newValue;
        }
    }
}

int distance(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    return sqrt(dx*dx + dy*dy);
}

void light_test(Image* image)
{
    int w = image->dibHeader->width;
    int h = image->dibHeader->height;

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            Pixel* pixel = pixel_at(image, x, y);
            int pixel_distance_from_light = distance(x, y, 30, 30);
            float light_power = 2.3f;

            int x_relative_to_light = abs(x - 30) % 4;
            int y_relative_to_light = abs(y - 30) % 4;

            int temp = (pixel_distance_from_light / light_power <= mat4[x_relative_to_light][y_relative_to_light] || 
                pixel_distance_from_light < light_power * 8) ? 1 : 0;
            pixel->r = pixel->r * temp;
            pixel->g = pixel->g * temp;
            pixel->b = pixel->b * temp;
        }
    }
}