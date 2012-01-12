// sphere.cc

#include "sphere.h"

// maybe float is enough, use double otherwise
#define FLOAT_T float

    // page 34 in "Realistic Ray Tracing":
    // (d*d)t^2 + 2d*(o-c)t + (o-c)*(o-c) - R^2
    // => equals classic quadratic equation:
    // At^2 + Bt + C = 0
Sphere::Sphere(const Vector3& _center, float _radius, const rgb& _color)
    : center(_center), radius(_radius), color(_color)
{ }

bool Sphere::hit(const Ray& r, float tmin, float tmax, \
                float time, HitRecord& record) const {
    // (o-c)
    Vector3 temp = r.origin() - center;

    // (d*d)
    FLOAT_T a = dot(r.direction(), r.direction());
    // 2d*(o-c)
    FLOAT_T b = 2*dot(r.direction(), temp);
    // (o-c)*(o-c)
    FLOAT_T c = dot(temp, temp) - radius*radius;
    // this is the term under the square-root 
    // (see solution for quadratc equation)
    FLOAT_T discriminant = b*b - 4*a*c;

    //first check if ray intersects sphere
    if (discriminant > 0) {
        discriminant = sqrt(discriminant);
        FLOAT_T t = (-b - discriminant) / (2*a);

        // check for valid interval
        if (t < tmin) t = (-b + discriminant) / (2*a);
        if (t < tmin || t > tmax) return false;

        // all good, assign values
        record.t = t;
        record.normal = unitVector(r.origin() + t*r.direction() - center);
        record.color = color;
        return true;
    }

    return false;
}

bool Sphere::shadowHit(const Ray& r, float tmin, float tmax, \
                float time) const {
    Vector3 temp = r.origin() - center;

    FLOAT_T a = dot(r.direction(), r.direction());
    FLOAT_T b = 2*dot(r.direction(), temp);
    FLOAT_T c = dot(temp, temp) - radius*radius;

    FLOAT_T discriminant = b*b - 4*a*c;

    //first check if ray intersects sphere
    if (discriminant > 0) {
        discriminant = sqrt(discriminant);
        FLOAT_T t = (-b - discriminant) / (2*a);

        // check for valid interval
        if (t < tmin) t = (-b + discriminant) / (2*a);
        if (t < tmin || t > tmax) return false;

        // all good
        return true;
    }

    return false;
}

