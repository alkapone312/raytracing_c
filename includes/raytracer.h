#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include "scene.h"
#include "ray.h"

#define RAYS_PER_PIXEL 100
#define RAY_BLUR 0.003
#define MAX_DEPTH 10

typedef struct Camera {
    Vec3 position;
    Vec3 direction;
    Vec3 up;
    double fov;
    double aspect_ratio;
} Camera;

Ray create_ray(Camera camera, double v_x, double v_y, double square);

Color cast_ray(const Ray ray, Scene* scene);

#endif // RAYTRACER_H_