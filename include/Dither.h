#pragma once

#include "Image.h"

extern int mat[4][4];
int distance(int x1, int y1, int x2, int y2);
void dither(Image* image);
void light_test(Image* image);