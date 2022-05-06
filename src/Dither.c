#include "Dither.h"

#include <math.h>

int mat[4][4] = 
{
    {0, 8, 2, 10},
    {12, 4, 14, 6},
    {3, 11, 1, 9},
    {15, 7, 13, 5}
};


void dither(Image* image)
{
    int w = image->dibHeader->width;
    int h = image->dibHeader->height;

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            Pixel* pixel = pixel_at(image, x, y);

            float normValue = pixel->r / 255.f;
            int newValue = (normValue < ((1.f/16) * (float)mat[x % 4][y % 4])) ? 0 : 255;

            pixel->r = newValue;
            pixel->g = newValue;
            pixel->b = newValue;
            
            // pixel->r = nearest_palette_col(pixel->r + (1.f/4) * (((1.f/16) * mat[x % 4][y % 4]) - 1.f/2));
            // pixel->g = nearest_palette_col(pixel->g + (1.f/4) * (((1.f/16) * mat[x % 4][y % 4]) - 1.f/2));
            // pixel->b = nearest_palette_col(pixel->b + (1.f/4) * (((1.f/16) * mat[x % 4][y % 4]) - 1.f/2));
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

            int temp = (pixel_distance_from_light / light_power <= mat[x_relative_to_light][y_relative_to_light] || 
                pixel_distance_from_light < light_power * 8) ? 1 : 0;
            pixel->r = pixel->r * temp;
            pixel->g = pixel->g * temp;
            pixel->b = pixel->b * temp;
        }
    }
}