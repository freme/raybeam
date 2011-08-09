// vector3.cc

#include "vector3.h"
#include <iostream>

std::istream& operator>>(std::istream& is, Vector3& t) {
    float temp;

    is >> temp;
    t.e[0] = temp;
    is >> temp;
    t.e[1] = temp;
    is >> temp;
    t.e[2] = temp;

    return is;
}

std::ostream& operator<<(std::ostream& os, const Vector3& t) {
    os << '('
        << t.e[0] << " "
        << t.e[1] << " "
        << t.e[2] << ')';

    return os;
}

float tripleProduct(const Vector3& v1, const Vector3& v2, const Vector3& v3)
{ return dot((cross(v1, v2)), v3); }

