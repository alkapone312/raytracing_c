#ifndef RENDER_H
#define RENDER_H

#include "vector.h"
#include "image.h"

#define RAYS_PER_PIXEL 100
#define RAY_BLUR 0.003
#define MAX_DEPTH 10

typedef struct Sphere {
    Vec3 position;
    Color color;
    double r;
} Sphere;

typedef struct Ray {
    Vec3 starting_position;
    Vec3 direction;
} Ray;

typedef struct HitInfo {
    Vec3 intersection;
    Vec3 normal;
    double t;
} HitInfo;

typedef struct Camera {
    Vec3 position;
    Vec3 direction;
    Vec3 up;
    double fov;
    double aspect_ratio;
} Camera;


int hit_sphere(const Ray ray, const Sphere sphere, HitInfo *hit);

Ray create_ray(Camera camera, double v_x, double v_y, double square);

Color cast_ray(const Ray ray, Sphere* spheres, int scene_size);

#endif