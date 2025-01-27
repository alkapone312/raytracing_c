#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
#include "image.h"

double drandom();

double drandom_mm(double min, double max);

int save_image_to_png(const char* filename, const Image image);

#endif