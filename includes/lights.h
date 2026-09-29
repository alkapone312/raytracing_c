#ifndef LIGHTS_H_
#define LIGHTS_H_

#include "ray.h"
#include "scene.h"

typedef struct PointLight {
    LIGHT_HEADER
    Vec3 position;
    double intensity;
} PointLight;

Color calculate_point_light_contribution(void* this, Scene* scene, HitInfo hit);

#define POINT_LIGHT(p, c, i) (PointLight) { \
    .calculate_light_contribution = calculate_point_light_contribution, \
    .color = c, \
    .position = p, \
    .intensity = i \
};

#endif // LIGHTS_H_