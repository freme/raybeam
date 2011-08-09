#include "vector3.h"

int main() {
    Vector3 vec1(2.0f, 2.0f, 2.0f);
    Vector3 vec2(1.0f, 2.0f, 3.0f);
    Vector3 temp;
    float ftmp = 0.0f;

    std::cout << "length = " << vec1.length() << std::endl;
    std::cout << "squaredlength = " << vec1.squaredLength() << std::endl;
    std::cout << "minComponent = " << vec2.minComponent() << std::endl;
    std::cout << "maxComponent = " << vec2.maxComponent() << std::endl;
    std::cout << "maxAbsComponent = " << vec2.maxAbsComponent() << std::endl;
    std::cout << "minAbsComponent = " << vec2.minAbsComponent() << std::endl;
    std::cout << "indexOfMinComponent = " << vec2.indexOfMinComponent() << std::endl;
    std::cout << "indexOfMaxComponent = " << vec2.indexOfMaxComponent() << std::endl;
    std::cout << "indexOfMaxAbsComponent = " << vec2.indexOfMaxAbsComponent() << std::endl;
    std::cout << "indexOfMinAbsComponent = " << vec2.indexOfMinAbsComponent() << std::endl;

    std::cout << "vec1 = " << vec1 << std::endl;
    std::cout << "vec2 = " << vec2 << std::endl;

    temp = vec1 + vec2;
    std::cout << "vec1 + vec2 = " << temp << std::endl;

    temp = vec1 - vec2;
    std::cout << "vec1 - vec2 = " << temp << std::endl;

    temp = vec1 * 2.0f;
    std::cout << "vec1 * 2.0f = " << temp << std::endl;

    temp = vec1 / 2.0f;
    std::cout << "vec1 / 2.0f = " << temp << std::endl;

    temp = cross(vec1, vec2);
    std::cout << "cross(vec1, vev2) = " << temp << std::endl;

    ftmp = dot(vec1, vec2);
    std::cout << "dot(vec1, vec2) = " << ftmp << std::endl;

    ftmp = tripleProduct(vec1, vec2, vec2);
    std::cout << "tripleProduct(vec1, vec2) = " << ftmp << std::endl;



    return 0;
}

