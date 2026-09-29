#include <math.h>
#include "utils.h"
#include "raytracer.h"

static Color calculate_lightning(Scene* scene, HitInfo hit) {
    Color result = COLOR_BLACK;
    for (int i = 0; i < scene->lights_count; i++) {
        Light* light = (Light*)scene->lights[i];

        Color contribution =
            light->calculate_light_contribution(
                light,
                scene,
                hit
            );

        result = add_color(result, contribution);
    }

    return result;
}

double depth = 0;
Color cast_ray(const Ray ray, Scene* scene) {
    Color final_color = COLOR_BLACK;
    HitInfo hit = {0};
    hit.distance = INFINITY;
    for(size_t i = 0; i < scene->objects_count; i++) {
        Object* o = (Object*) scene->objects[i];
        if(o->hit(o, ray, &hit) == 1) {
            
            // Debug normals
            // return (Color) {
            //     (hit.normal.x + 1.0) * 0.5 * 255.0, 
            //     (hit.normal.y + 1.0) * 0.5 * 255.0, 
            //     (hit.normal.z + 1.0) * 0.5 * 255.0, 
            //     255
            // };

            Color light_color = calculate_lightning(scene, hit);
            Color surface_color = multiply_color(light_color, o->material.base_color);

            Vec3 random = add(hit.normal, random_unit());
            if (dot(random, hit.normal) > 0.0) {
                random = smul(random, -1);
            }
            
            if (depth++ < MAX_DEPTH) {
                final_color = cast_ray(
                    (Ray) {.direction = random, .starting_position = hit.intersection},
                    scene
                );
            }
            depth--;

            final_color = add_color(final_color, surface_color);
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
        smul(viewport_y, 0.5 - v_y + square_y)
    );
    const Vec3 direction = unit(sub(pixel_coord, camera.direction));
    
    return (Ray) {
        .starting_position = camera.position,
        .direction = direction
    };
}
