#pragma once

#include "Image.h"

extern int mat2[2][2];
extern int mat4[4][4];
extern int mat8[8][8];

// Testing
int distance(int x1, int y1, int x2, int y2);
void light_test(Image* image);

// Coloroured bayer dithering
void dither_color_8x8(Image* image);

// Grayscale bayer dithering
void dither_grayscale_2x2(Image* image);
void dither_grayscale_4x4(Image* image);
void dither_grayscale_8x8(Image* image);
