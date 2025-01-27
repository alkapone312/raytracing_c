#ifndef VECTOR_H
#define VECTOR_H

typedef struct Vec3 {
    double x;
    double y;
    double z;
} Vec3;

Vec3 cross(Vec3 a, Vec3 b);

double dot(Vec3 a, Vec3 b);

Vec3 add(Vec3 a, Vec3 b);

Vec3 sub(Vec3 a, Vec3 b);

double length(Vec3 a);

Vec3 unit(Vec3 a);

Vec3 smul(Vec3 a, double s);

Vec3 random_unit();

#endif
