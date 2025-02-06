#ifndef SCENE_H_
#define SCENE_H_

#include <stddef.h>
#include <stdbool.h>
#include "ray.h"

#define OBJECT_HEADER bool (*hit)(void* this, Ray, HitInfo*);

typedef struct Object {
    OBJECT_HEADER
} Object;

typedef struct Scene {
    void** objects;
    size_t count;
} Scene;

#endif // SCENE_H_