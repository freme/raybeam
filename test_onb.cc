#include "onb.h"
#include <cstdio>

int main() {
    Vector3 vec1(1.0f, 1.0f, 1.0f);
    Vector3 vec2(1.0f, 3.0f, 6.0f);
    Vector3 vec3(2.0f, 4.0f, 3.0f);

    std::cout << "vec1 = " << vec1 << std::endl;
    std::cout << "vec2 = " << vec2 << std::endl;
    std::cout << "vec3 = " << vec3 << std::endl;

    ONB onb1;
    ONB onb2;
    ONB onb3;

    ONB otmp(vec1, vec2, vec3);

    onb1.initFromU(vec1);
    onb2.initFromV(vec2);
    onb3.initFromW(vec3);

    std::cout << "onb1:\n" << onb1 << std::endl;
    std::cout << "onb2:\n" << onb2 << std::endl;
    std::cout << "onb3:\n" << onb3 << std::endl;
    std::cout << "otmp:\n" << otmp << std::endl;

    onb1.initFromUV(vec1, vec2);
    std::cout << "initFromUV(vec1, vec2):\n" << onb1 << std::endl;

    onb1.initFromVU(vec1, vec2);
    std::cout << "initFromVU(vec1, vec2):\n" << onb1 << std::endl;

    onb2.initFromVU(vec2, vec1);
    std::cout << "initFromVU(vec2, vec1):\n" << onb2 << std::endl;

    if (onb1 == onb2) printf("onb1 == onb2\n\n");
    else printf("onb1 != onb2\n\n");

    onb1.initFromUW(vec1, vec2);
    std::cout << "initFromUW(vec1, vec2):\n" << onb1 << std::endl;

    onb1.initFromWU(vec1, vec2);
    std::cout << "initFromWU(vec1, vec2):\n" << onb1 << std::endl;

    onb1.initFromVW(vec1, vec2);
    std::cout << "initFromVW(vec1, vec2):\n" << onb1 << std::endl;

    onb1.initFromWV(vec1, vec2);
    std::cout << "initFromWV(vec1, vec2):\n" << onb1 << std::endl;



    return 0;
}

