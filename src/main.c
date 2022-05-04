#include <stdio.h>
#include <math.h>

#include "Image.h"

int main()
{
    Image* image = load_image("bunny.bmp");

    int w = image->dibHeader->width;
    int h = image->dibHeader->height;

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            Pixel* pixel = pixel_at(image, x, y);
            // float factor = 3.f;
            // pixel->r = round(factor * pixel->r / 255.f) * (255 / factor);
            // pixel->g = round(factor * pixel->g / 255.f) * (255 / factor);
            // pixel->b = round(factor * pixel->b / 255.f) * (255 / factor);

            pixel->r = 255 - pixel->r;
            pixel->g = 255 - pixel->g;
            pixel->b = 255 - pixel->b;
        }
    }

    save_image("bunny1.bmp", image);
    return 0;
}