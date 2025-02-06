#include <math.h>
#include "utils.h"
#include "raytracer.h"

double depth = 0;
Color cast_ray(const Ray ray, Scene* scene) {
    const double light_intensity = 1;
    Color final_color = COLOR_WHITE;
    HitInfo hit = {0};
    hit.t = INFINITY;
    for(int i = 0 ; i < scene->count; i++) {
        Object* o = (Object*) scene->objects[i];
        if(o->hit(o, ray, &hit) == 1) {
            Vec3 random = add(hit.normal, random_unit());
            if(dot(random, hit.normal) > 0.0)
                random = smul(random, -1);
            
            if(depth++ < MAX_DEPTH)
                final_color = cast_ray(
                    (Ray) {.direction = random, .starting_position = hit.intersection},
                    scene
                );
            depth--;
            
            final_color.red /= 2;
            final_color.green /= 2;
            final_color.blue /= 2;
        }
    }

    return final_color;
}

Ray create_ray(Camera camera, double v_x, double v_y, double square) {
    double square_x = square * drandom_mm(-1, 1);
    double square_y = square * drandom_mm(-1, 1); 
    const Vec3 viewport_x = unit(cross(camera.direction, camera.up));
    const Vec3 viewport_y = unit(cross(camera.direction, viewport_x));
    const Vec3 pixel_coord = add(
        smul(viewport_x, (v_x - 0.5) * camera.aspect_ratio + square_x), 
        smul(viewport_y, v_y - 0.5 + square_y)
    );
    const Vec3 direction = sub(add(pixel_coord, camera.direction), camera.position);

    return (Ray) {
        .starting_position = camera.position,
        .direction = direction
    };
}
