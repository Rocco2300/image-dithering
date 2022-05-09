#pragma once

#include "Image.h"

// For individual pixels
void quantize_pixel(Pixel* pixel, int factor);

// For whole image
void grayscale(Image* image);
void quantize(Image* image, int factor);