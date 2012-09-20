// uvsphere.h

#ifndef _UV_SPHERE_
#define _UV_SPHERE_ 1

#include "shape.h"
#include "vector3.h"
#include "ray.h"
#include "texture.h"

class UVSphere : public Shape {
    public:
        UVSphere(const Vector3& _center, float _radius, Texture* tex);
        //BBox boundingBox() const;
        bool hit(const Ray& r, float tmin, float tmax, float time, HitRecord& record) const;
        bool shadowHit(const Ray& r, float tmin, float tmax, float time) const;

        Vector3 center;
        float radius;
        Texture* tex;
};

#endif // _TEXTURE_H_
