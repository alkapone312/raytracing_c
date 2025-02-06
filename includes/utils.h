#ifndef UTILS_H_
#define UTILS_H_

#include "image.h"

double drandom();

double drandom_mm(double min, double max);

int save_image_to_png(const char* filename, const Image image);

#endif // UTILS_H_