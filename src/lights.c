#include "lights.h"
#include <math.h>
#include "stdio.h"

#define SHADOW_EPSILON 0.001

Color calculate_point_light_contribution(void* this, Scene* scene, HitInfo hit) {
    PointLight* light = (PointLight*)this;
    Vec3 to_light = sub(light->position, hit.intersection);
    double distance = length(to_light);
    if (distance <= SHADOW_EPSILON) {
        return COLOR_BLACK;
    }

    Vec3 light_direction = smul(to_light, 1.0 / distance);
    double diffuse = dot(hit.normal, light_direction);
    if (diffuse <= 0.0) {
        return COLOR_BLACK;
    }

    Ray shadow_ray = {
        .starting_position = add(hit.intersection, smul(hit.normal, SHADOW_EPSILON)),
        .direction = light_direction
    };

    for (size_t i = 0; i < scene->objects_count; i++) {
        Object* object = (Object*)scene->objects[i];

        HitInfo shadow_hit = {0};
        shadow_hit.distance = INFINITY;

        if (object->hit(object, shadow_ray, &shadow_hit)) {
            if (shadow_hit.distance > SHADOW_EPSILON && shadow_hit.distance < distance) {
                return COLOR_BLACK;
            }
        }
    }

    double attenuation = 1.0;// / (distance * distance);
    double factor = diffuse * attenuation * light->intensity;

    Color result;
    result.red = (uint8_t)fmin(
        255.0,
        light->color.red * factor
    );
    result.green = (uint8_t)fmin(
        255.0,
        light->color.green * factor
    );
    result.blue = (uint8_t)fmin(
        255.0,
        light->color.blue * factor
    );
    result.alpha = 255;

    return result;
}