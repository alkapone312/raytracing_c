#include <math.h>
#include "sphere.h"

bool hit_sphere(void* this, Ray ray, HitInfo* info) {
    Sphere* sphere = (Sphere*) this;
    Vec3 oc = sub(ray.starting_position, sphere->center);
    double a = dot(ray.direction, ray.direction);
    double b = 2.0 * dot(oc, ray.direction);
    double c = dot(oc, oc) - sphere->radius * sphere->radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return false;
    }

    double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b + sqrt(discriminant)) / (2.0 * a);

    if (t1 < 0 && t2 < 0) {
        return false;
    }

    double t = INFINITY;
    if (t1 > 0.0001)
        t = t1;

    if (t2 > 0.0001 && t2 < t)
        t = t2;

    if (t == INFINITY)
        return false;

    // Don't hit if already hitted closer point
    // Don't hit yourself
    if(info->distance < t || t < 0.0001) {
        return false; 
    }

    info->distance = t;
    info->intersection = (Vec3) {
        ray.starting_position.x + t * ray.direction.x,
        ray.starting_position.y + t * ray.direction.y,
        ray.starting_position.z + t * ray.direction.z
    };
    info->normal = unit(sub(info->intersection, sphere->center));

    return true;
}
