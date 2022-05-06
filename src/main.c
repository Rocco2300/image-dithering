#include <stdio.h>
#include <math.h>

#include "Dither.h"
#include "Effects.h"
#include "Image.h"

Image* get_white_img()
{
    Image* image = create_image(60, 60);

    int w = image->dibHeader->width;
    int h = image->dibHeader->height;

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            Pixel* pixel = pixel_at(image, x, y);

            pixel->r = 255;
            pixel->g = 255;
            pixel->b = 255;
        }
    }

    return image;
}

int main()
{
    Image* white_image = get_white_img();
    // Image* image = load_image("Circle1.bmp");

    // quantize(image, 4);
    // grayscale(image);
    // dither(image);
    light_test(white_image);

    save_image("dither.bmp", white_image);
    return 0;
}