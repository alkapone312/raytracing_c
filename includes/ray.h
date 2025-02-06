#ifndef RAY_H_
#define RAY_H_

#include "vector.h"

typedef struct Ray {
    Vec3 starting_position;
    Vec3 direction;
} Ray;

typedef struct HitInfo {
    Vec3 intersection;
    Vec3 normal;
    double t;
} HitInfo;

#endif // RAY_H_