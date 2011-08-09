// test_rng.cc

#include "rng.h"
#include <iostream>

int main() {
    RNG rnd;
    
    std::cout << "some random numbers: " << std::endl; 
    for (int i = 0; i < 10; i++) {
        std::cout << rnd() << " ";
        std::cout << rnd() << " ";
        std::cout << rnd() << " ";
        std::cout << std::endl;
    }

    return 0;
}
