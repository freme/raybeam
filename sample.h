#ifndef _SAMPLE_H_
#define _SAMPLE_H_

#include "vector2.h"
#include <math.h>

// 2D sampling
void random(Vector2* samples, int num_samples);

// jitter assumes num_samples is a perfect square
void jitter(Vector2* samples, int num_samples);
void nrooks(Vector2* samples, int num_samples);

// multiJitter assumes num_samples is a perfect square
void multiJitter(Vector2* samples, int num_samples);
void shuffle(Vector2* samples, int num_samples);

void boxFilter(Vector2* samples, int num_samples);
void tentFilter(Vector2* samples, int num_samples);
void cubicSplineFilter(Vector2* samples, int num_samples);

// 1D sampling
void random(float* samples, int num_samples);
void jitter(float* samples, int num_samples);
void shuffle(float* samples, int num_samples);

// helper function for cubicSplineFilter
inline float solve(float r) {
    float u = r;
    for (int i = 0; i < 5; i++)
        u = (11.0f * r + u * u * (6.0f + u * (8.0f - 9.0f * u))) / 
            (4.0f + 12.0f * u * (1.0f + u * (1.0f - u)));
    return u;
}

// helper function for cubicSplineFilter
inline float cubicFilter(float x) {
    if (x < 1.0f / 24.0f) return pow(24 * x, 0.25f) - 2.0f;
    else if (x < 0.5) return solve(24.0f * (x - 1.0f / 24.0f) / 11.0f) - 1.0f;
    else if (x < 23.0f / 24.0f) return 1.0f - solve(24.0f * (23.0f / 24.0f - x) / 11.0f);
    else return 2 - pow(24.0f * (1.0f - x), 0.25f);
}

#endif // _SAMPLE_H_
