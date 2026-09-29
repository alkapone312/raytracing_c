#ifndef SCENE_H_
#define SCENE_H_

#include <stddef.h>
#include <stdbool.h>
#include "ray.h"
#include "image.h"

#define OBJECT_HEADER \
bool (*hit)(void* this, Ray, HitInfo*); \
Material material;

#define LIGHT_HEADER \
Color (*calculate_light_contribution)(void* this, Scene* scene, HitInfo hit); \
Color color;

typedef struct Scene {
    void** objects;
    void** lights;
    size_t objects_count;
    size_t lights_count;
} Scene;

typedef struct Material {
    Color base_color;
} Material;

typedef struct Light {
    LIGHT_HEADER
} Light;

typedef struct Object {
    OBJECT_HEADER
} Object;

#endif // SCENE_H_