#include <stdio.h>

#include "Effects.h"
#include "Image.h"

int main()
{
    Image* image = load_image("bunny.bmp");

    grayscale(image);
    quantize(image, 1);

    save_image("bunny1.bmp", image);
    return 0;
}