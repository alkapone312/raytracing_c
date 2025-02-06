#ifndef SPHERE_H_
#define SPHERE_H_

#include "ray.h"
#include "scene.h"

typedef struct Sphere {
    OBJECT_HEADER
    Vec3 center;
    int diameter;
} Sphere;

bool hit_sphere(void* this, Ray, HitInfo*);

#define SPHERE(c, d) (Sphere) {.hit = hit_sphere, .center = c, .diameter = d};

#endif // SPHERE_H_