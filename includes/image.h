#ifndef IMAGE_H_
#define IMAGE_H_

#include <stdint.h>
#include <stdlib.h>

#define SUCCESS 0
#define OUT_OF_BOUNDS 1

#define COLOR_BLACK (Color){0, 0, 0, 255}
#define COLOR_WHITE (Color){255, 255, 255, 255}
#define COLOR_RED   (Color){255, 0, 0, 255}
#define COLOR_GREEN (Color){0, 255, 0, 255}
#define COLOR_BLUE  (Color){0, 0, 255, 255}
#define COLOR(r, g, b, a) ((Color){(r), (g), (b), (a)})

typedef struct Color
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
} Color;

typedef struct Image
{
    uint64_t width;
    uint64_t height;
    Color* screen;
} Image;

int set_pixel(Image image, uint64_t x, uint64_t y, Color color);

int get_pixel(Image image, uint64_t x, uint64_t y, Color* color);

Image create_image(uint64_t width, uint64_t height);

void destroy_image(Image image);

#endif // IMAGE_H_