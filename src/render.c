#include <math.h>
#include "render.h"
#include "utils.h"

int hit_sphere(const Ray ray, const Sphere sphere, HitInfo *hit) {
    Vec3 oc = sub(ray.starting_position, sphere.position);
    double a = dot(ray.direction, ray.direction);
    double b = -2.0 * dot(oc, ray.direction);
    double c = dot(oc, oc) - sphere.r * sphere.r;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return 0;
    }

    double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
    double t2 = (-b + sqrt(discriminant)) / (2.0 * a);

    if (t1 < 0 && t2 < 0) {
        return 0;
    }

    double t = t1 < t2 ? t1 : t2;

    // Don't hit if already hitted closer point
    // Don't hit yourself
    if(hit->t < t || t < 0.0001) {
        return 0; 
    }

    hit->t = t;
    hit->intersection = (Vec3) {
        ray.starting_position.x - t * ray.direction.x,
        ray.starting_position.y - t * ray.direction.y,
        ray.starting_position.z - t * ray.direction.z
    };
    hit->normal = unit(sub(hit->intersection, sphere.position));

    return 1;
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

double depth = 0;
Color cast_ray(const Ray ray, Sphere* spheres, int scene_size) {
    const double light_intensity = 1;
    Color final_color = COLOR_WHITE;
    HitInfo hit = {0};
    hit.t = INFINITY;
    for(int i = 0 ; i < scene_size; i++) {
        if(hit_sphere(ray, spheres[i], &hit) == 1) {
            Vec3 random = add(hit.normal, random_unit());
            if(dot(random, hit.normal) > 0.0)
                random = smul(random, -1);
            
            if(depth++ < MAX_DEPTH)
                final_color = cast_ray(
                    (Ray) {.direction = random, .starting_position = hit.intersection},
                    spheres,
                    scene_size
                );
            depth--;
            
            final_color.red /= 2;
            final_color.green /= 2;
            final_color.blue /= 2;
        }
    }

    return final_color;
}
