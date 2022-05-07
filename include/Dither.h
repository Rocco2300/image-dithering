#pragma once

#include "Image.h"

extern int mat4[4][4];
extern int mat8[8][8];

int distance(int x1, int y1, int x2, int y2);
void dither_grayscale_4x4(Image* image);
void dither_grayscale_8x8(Image* image);
void light_test(Image* image);