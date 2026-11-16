#include "image.h"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

int set_pixel(Image image, uint64_t x, uint64_t y, Color color) {
    if(x < 0 || y < 0 || x > image.width || y > image.height) {
        return OUT_OF_BOUNDS;
    }

    image.screen[y*image.width+x] = color;

    return SUCCESS;
}

int get_pixel(Image image, uint64_t x, uint64_t y, Color* color) {
    if(x < 0 || y < 0 || x > image.width || y > image.height) {
        return OUT_OF_BOUNDS;
    }

    Color c = image.screen[y*image.width+x];
    color->red = c.red;
    color->green = c.green;
    color->blue = c.blue;
    color->alpha = c.alpha;

    return SUCCESS;
}

Image create_image(uint64_t width, uint64_t height) {
    Color* screen = (Color*) malloc(width * height * sizeof(Color));

    Image image = {
        .width = width,
        .height = height,
        .screen = screen
    };

    return image;
}

void destroy_image(Image image) {
    free(image.screen);
}

Color add_color(Color a, Color b) {
    Color result;

    result.red = MIN(255, (int)a.red + (int)b.red);
    result.green = MIN(255, (int)a.green + (int)b.green);
    result.blue = MIN(255, (int)a.blue + (int)b.blue);
    result.alpha = a.alpha;

    return result;
}

Color multiply_color(Color a, Color b)
{
    Color result;

    result.red = (uint8_t)((uint32_t)a.red * b.red / 255);
    result.green = (uint8_t)((uint32_t)a.green * b.green / 255);
    result.blue = (uint8_t)((uint32_t)a.blue * b.blue / 255);
    result.alpha = a.alpha;

    return result;
}