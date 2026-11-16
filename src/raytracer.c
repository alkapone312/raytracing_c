#include <math.h>
#include "utils.h"
#include "image.h"
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

Color cast_ray(const Ray ray, Scene *scene, int depth) {
    HitInfo closest_hit = {0};
    closest_hit.distance = INFINITY;

    Object *closest_object = NULL;

    for (size_t i = 0; i < scene->objects_count; i++) {
        Object *obj = (Object *)scene->objects[i];
        HitInfo temp_hit = {0};
        temp_hit.distance = INFINITY;

        if (obj->hit(obj, ray, &temp_hit) == 1) {
            if (temp_hit.distance > 0.0 && temp_hit.distance < closest_hit.distance) {
                closest_hit = temp_hit;
                closest_object = obj;
            }
        }
    }

    if (closest_object == NULL) {
        return COLOR_BLACK;
    }

    Color light_color = calculate_lightning(scene, closest_hit);
    Color surface_color = multiply_color(light_color, closest_object->material.base_color);

    if (depth >= MAX_DEPTH) {
        return surface_color;
    }

    Vec3 random = add(closest_hit.normal, random_unit());
    if (dot(random, closest_hit.normal) < 0.0) {
        random = smul(random, -1.0);
    }

    Ray bounce_ray = {
        .starting_position = add(
            closest_hit.intersection,
            smul(closest_hit.normal, 0.001)
        ),
        .direction = random
    };

    Color bounce_color = cast_ray(bounce_ray, scene, depth + 1);
    bounce_color = multiply_color(bounce_color, closest_object->material.base_color);

    return add_color(surface_color, bounce_color);
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
