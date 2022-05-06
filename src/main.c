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