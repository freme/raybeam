#include "solid_noise.h"

int main() {
    SolidNoise test;
    int depth = 10;
    Vector3 vec(1.1f,  2.2f, 3.3f);

    std::cout << "Noise = " << test.noise(vec) << std::endl;
    std::cout << "Turbulence = " << test.turbulence(vec, depth) <<
    std::endl;
    std::cout << "DTurbulence = " << test.dturbulence(vec, depth, 7)
    << std::endl;

}
