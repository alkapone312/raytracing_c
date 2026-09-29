#ifndef SPHERE_H_
#define SPHERE_H_

#include "ray.h"
#include "scene.h"

typedef struct Sphere {
    OBJECT_HEADER
    Vec3 center;
    double radius;
} Sphere;

bool hit_sphere(void* this, Ray, HitInfo*);

#define SPHERE(m, c, r) (Sphere) { \
    .material = m, \
    .hit = hit_sphere, \
    .center = c, \
    .radius = r \
};

#endif // SPHERE_H_