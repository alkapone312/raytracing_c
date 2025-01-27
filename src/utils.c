#include <png.h>
#include "utils.h"

double drandom() {
    return (double) rand() / RAND_MAX;
}

double drandom_mm(double min, double max) {
    return drandom() * (max - min) + min;
}

int save_image_to_png(const char* filename, const Image image) {
    FILE* fp = fopen(filename, "wb");
    if (!fp) {
        perror("Failed to open file");
        return -1;
    }

    // Initialize write struct
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        fclose(fp);
        fprintf(stderr, "Failed to create png write struct\n");
        return -1;
    }

    // Initialize info struct
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_write_struct(&png_ptr, NULL);
        fclose(fp);
        fprintf(stderr, "Failed to create png info struct\n");
        return -1;
    }

    // Error handling
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_write_struct(&png_ptr, &info_ptr);
        fclose(fp);
        fprintf(stderr, "Failed during PNG creation\n");
        return -1;
    }

    // Set up output control
    png_init_io(png_ptr, fp);

    // Set image attributes
    png_set_IHDR(
        png_ptr,
        info_ptr,
        image.width,
        image.height,
        8, // Bit depth
        PNG_COLOR_TYPE_RGBA, // Color type
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
    );

    png_write_info(png_ptr, info_ptr);

    // Write the image data
    png_bytep row_pointers[image.height];
    for (uint64_t y = 0; y < image.height; y++) {
        row_pointers[image.height - y - 1] = (png_bytep) &image.screen[y * image.width];
    }
    png_write_image(png_ptr, row_pointers);

    // End write
    png_write_end(png_ptr, NULL);

    // Cleanup
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(fp);

    return 0;
}