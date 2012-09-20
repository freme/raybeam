// test_ray.cc

#include "../ray.h"

int main() {
    Ray r1;
    Vector3 a(1.0f, 2.0f, 3.0f);
    Vector3 b(4.0f, 5.0f, 6.0f);
    Ray r2(a, b);
    Ray r3(r1);

    std::cout << "origin:              " << r2.origin() \
        << std::endl;
    std::cout << "direction:           " << r2.direction() \
        << std::endl;
    std::cout << "pointAtParameter(2): " << r2.pointAtParameter(2.0f) \
        << std::endl;

    return 0;
}

