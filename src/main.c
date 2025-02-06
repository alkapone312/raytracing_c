#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "image.h"
#include "utils.h"
#include "sphere.h"
#include "raytracer.h"

#define WIDTH 400
#define HEIGHT 400

int main() {
    srand(time(NULL));
    Sphere s1 = SPHERE(((Vec3) {0, 0, -5}), 1);
    Sphere s2 = SPHERE(((Vec3) {0, -100, -5}), 99);

    void* objects[2] = {
        &s1, 
        &s2
    };

    Scene s = {
        .objects = objects,
        .count = 2
    };

    Camera camera = {
        .position = (Vec3) {0, 0, 0},
        .direction = (Vec3) {0, 0, 1},
        .up = (Vec3) {0, 1, 0},
        .fov = 90,
        .aspect_ratio = (double) WIDTH / HEIGHT
    };

    Image image = create_image(WIDTH, HEIGHT);
    for(int i = 0 ; i < WIDTH; i++) {
        for(int j = 0; j < HEIGHT; j++) {
            float r = 0, g = 0, b = 0;
            for(int k = 0; k < RAYS_PER_PIXEL; k++) {
                Ray ray = create_ray(camera, (double) i / WIDTH, (double) j / HEIGHT, RAY_BLUR);
                Color c = cast_ray(ray, &s);
                r += (float) c.red / RAYS_PER_PIXEL;
                g += (float) c.green / RAYS_PER_PIXEL;
                b += (float) c.blue / RAYS_PER_PIXEL;
            }
            set_pixel(image, i, j, COLOR(r, g, b, 255));
        }
    }
    save_image_to_png("output.png", image);

    destroy_image(image);
    return 0;
}