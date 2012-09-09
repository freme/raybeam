#include "vector2.h"
#include <iostream>

int main() {
    Vector2 vec1(1.0f, 2.0f);

    std::cout << "vec1 = (" << vec1.x() << " " << vec1.y() << ")"  << std::endl;

    return 0;
}

