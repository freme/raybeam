// rng.h

#ifndef _RNG_H_
#define _RNG_H_ 1

// #include <cstdint>
#include "stdint.h"

class RNG {
    public:
        RNG(uint64_t _seed = 7564231ULL)
        {
            seed        =   _seed;
            mult        =   62089911ULL;
            llong_max   =   4294967295ULL;
            float_max   =   4294967295.0f;
        }
        float operator()();

        uint64_t seed;
        uint64_t mult;
        uint64_t llong_max;
        float float_max;
};

inline float RNG::operator()() {
    seed = mult * seed;
    return float(seed % llong_max) / float_max;
}

#endif // _RNG_H_

