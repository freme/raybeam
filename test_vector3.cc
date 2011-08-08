#include "vector3.h"

int main() {
    Vector3* vec = new Vector3::Vector3(1, 2, 3);

    std::cout << "length = " << vec->length() << std::endl;

    return 0;
}

