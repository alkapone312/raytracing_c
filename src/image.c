#include "image.h"

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