// ray.h

#ifndef _RAY_H_
#define _RAY_H_ 1

#include "vector3.h"
#include <iostream>

class Ray {
    public:
        Ray() {}
        Ray(const Vector3& a, const Vector3& b)
        { data[0] = a; data[1] = b; }
        Ray(const Ray& r) { *this = r; }
        Vector3 origin() const { return data[0]; }
        Vector3 direction() const { return data[1]; }
        Vector3 pointAtParameter(float t) const
        { return data[0] + t*data[1]; }

        Vector3 data[2];
};

inline std::ostream& operator<<(std::ostream& os, const Ray& r) {
    os << '(' << r.origin() << ") + t(" << r.direction() << ')';
    return os;
}

#endif // _RAY_H_

