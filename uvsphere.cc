// uvsphere.cc 

#include "uvsphere.h"

UVSphere::UVSphere(const Vector3& _center, float _radius, Texture* _tex)
    : center(_center), radius(_radius), tex(_tex) {}

bool UVSphere::hit(const Ray& r, float tmin, float tmax, float time, HitRecord& record)const {
    Vector3 temp = r.origin() - center;

    double a = dot(r.direction(), r.direction());
    double b = 2*dot( r.direction(), temp);
    double c = dot(temp, temp) - radius*radius;

    double discriminant = b*b - 4.0*a*c;

    // first check to see if ray intersects sphere
    if ( discriminant > 0.0 ) {
        discriminant = sqrt(discriminant);
        double t = (-b -discriminant) /(2.0*a);

        //now check for valid interval
        if(t < tmin)
            t = ( - b + discriminant) / (2.0*a);
        if(t < tmin || t > tmax)
            return false;

        //we have a valid hit
        record.t = t;
        record.hit_p = (r.origin() + t* r.direction());
        Vector3 n = record.normal = (record.hit_p - center) / radius;

        //calculate UV coordinates
        float twopi = 6.28318530718f;
        float theta = acos( n.z());
        float phi   = atan2(n.y(), n.x());
        if(phi < 0.0f )
            phi += twopi;

        float one_over_2pi = .159154943092f;
        float one_over_pi =  .318309886184f;

        record.uv = Vector2(phi*one_over_2pi, (M_PI - theta) * one_over_pi);

        record.hit_tex = tex;
        return true;
    }
    return false;
}
bool UVSphere::shadowHit(const Ray& r, float tmin, float tmax, float time)const {
    Vector3 temp = r.origin() - center;

    double a = dot(r.direction(), r.direction());
    double b = 2*dot( r.direction(), temp);
    double c = dot(temp, temp) - radius*radius;

    double discriminant = b*b - 4.0*a*c;

    // first check to see if ray intersects sphere
    if ( discriminant > 0.0 ) {
        discriminant = sqrt(discriminant);
        double t = (-b -discriminant) /(2.0*a);

        //now check for valid interval
        if(t < tmin)
            t = ( - b + discriminant) / (2.0*a);
        if(t < tmin || t > tmax)
            return false;

        // valid hit
        return true;
    }
    return false;
}
    
