// test_surfaces.cc

#include "shape.h"
#include "triangle.h"
#include "sphere.h"
#include <iostream>

int main() {
    Vector3 p0(1.0f, 1.0f, 1.0f);
    Vector3 p1(1.0f, 2.0f, 1.0f);
    Vector3 p2(1.0f, 1.0f, 2.0f);
    rgb cr(0.5f, 0.0f, 0.0f);
    rgb cg(0.0f, 0.5f, 0.0f);
    rgb cb(0.0f, 0.0f, 0.5f);
    Ray r(p1, p2);
    HitRecord h = {1.0, p1, cb};

    Triangle t(p0, p1, p2, cr);
    Sphere s(p0, 1.0f, cg);

    bool ret = false;

    ret = t.hit(r, 0.0f, 10.0f, 0.0f, h);
    if (ret) std::cout << "ray->triangle: hit" << std::endl;

    ret = s.hit(r, 0.0f, 10.0f, 0.0f, h);
    if (ret) std::cout << "ray->sphere: hit" << std::endl;

    return 0;
}

