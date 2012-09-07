#ifndef _SHAPE_H_
#define _SHAPE_H_ 1

#include "ray.h"
//#include "vector3.h"
#include "rgb.h"
#include "texture.h"

// this shouldn't be needed
//class Ray;
//class rgb;

struct HitRecord {
    float t;
    Vector3 normal;
    rgb color;
    Vector2 uv;
    Vector3 hit_p;
    Texture* hit_tex;
};

class Shape {
    public:
        virtual bool hit(const Ray& r, float tmin, float tmax, \
                float time, HitRecord& record) const = 0;
        virtual bool shadowHit(const Ray& r, float tmin, float tmax, \
                float time) const = 0;
};

#endif // _SHAPE_H_

