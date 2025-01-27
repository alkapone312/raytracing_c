#include <math.h>
#include "vector.h"
#include "utils.h"

Vec3 cross(Vec3 a, Vec3 b) {
    return (Vec3) {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

double dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 add(Vec3 a, Vec3 b) {
    return (Vec3) {
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    };
}

Vec3 sub(Vec3 a, Vec3 b) {
    return (Vec3) {
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    };
}

double length(Vec3 a) {
    return sqrt(dot(a, a));
}

Vec3 unit(Vec3 a) {
    const double len = length(a);
    return (Vec3) {a.x / len, a.y / len, a.z / len};
}

Vec3 smul(Vec3 a, double s) {
    return (Vec3) {a.x * s, a.y * s, a.z * s};
}

Vec3 random_unit() {
    Vec3 v = {drandom_mm(-1, 1), drandom_mm(-1, 1), drandom_mm(-1, 1)};
    while(length(v) == 0.0) {
        v = (Vec3) {drandom_mm(-1, 1), drandom_mm(-1, 1), drandom_mm(-1, 1)};
    }

    return unit(v);
}