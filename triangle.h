// triangle.h

#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_ 1

#include "shape.h"
//#include "vector3.h"
//#include "rgb.h"
//#include "ray.h"

class Triangle : public Shape {
    public:
        Triangle(const Vector3& _p0, const Vector3& _p1, \
                const Vector3& _p2, const rgb& _color);
        bool hit(const Ray& r, float tmin, float tmax, \
                float time, HitRecord& record) const;
        bool shadowHit(const Ray& r, float tmin, float tmax, \
                float time) const;

        Vector3 p0;
        Vector3 p1;
        Vector3 p2;
        rgb color;
};

#endif // _TRIANGLE_H_

