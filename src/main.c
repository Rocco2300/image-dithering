#include <stdio.h>
#include <math.h>

#include "Effects.h"
#include "Image.h"

int mat[4][4] = 
{
    {0, 8, 2, 10},
    {12, 4, 14, 6},
    {3, 11, 1, 9},
    {15, 7, 13, 5}
};

int nearest_palette_col(int color)
{
    return (color < (255/2)) ? 0 : 255;
    // return round(3 * color / 255.f) * (255.f / 3);
}

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

int main()
{
    Image* image = load_image("Circle1.bmp");

    // quantize(image, 4);
    // grayscale(image);
    dither(image);

    save_image("dither.bmp", image);
    return 0;
}