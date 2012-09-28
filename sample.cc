// sample.cc
//
#include "sample.h"
#include "vector2.h"
#include <math.h>
#include <stdlib.h>
#include "rng.h"

// deterministic; repeatable pseudo rng numbers ;)
RNG rng;

// more pseudo rngness
//#define rng drng48

// cryptogrphic rng
//#define rng() (arc4rng() % ((unsigned)RAND_MAX + 1))

void random(Vector2* samples, int num_samples) {
    for (int i = 0; i < num_samples; i++) {
        samples[i].setX(rng());
        samples[i].setY(rng());
    }
}

// assumes num_samples is a perfect square
void jitter(Vector2* samples, int num_samples) {
    int sqrt_samples = (int)(sqrt(num_samples));
    for(int i = 0; i < sqrt_samples; i++)
        for(int j = 0; j < sqrt_samples; j++) {
            float x = ((double)i + rng()) / (double)sqrt_samples;
            float y = ((double)j + rng()) / (double)sqrt_samples;
            (samples[i*sqrt_samples + j]).setX(x);
            (samples[i*sqrt_samples + j]).setY(y);
        }
}

void nrooks(Vector2* samples, int num_samples) {
    for (int i = 0; i < num_samples; i++) {
        samples[i].setX(((double)i + rng()) / (double)num_samples);
        samples[i].setY(((double)i + rng()) / (double)num_samples);
    }
    //shuffle the x-coords
    for (int i = num_samples - 2; i >= 0; i--) {
        int target = int(rng() * (double)i);
        float temp = samples[i+1].x();
        samples[i+1].setX(samples[target].x());
        samples[target].setX(temp);
    }
}

// assumes num_samples is a perfect square
void multiJitter(Vector2* samples, int num_samples) {
    int sqrt_samples = (int)(sqrt(num_samples));
    float subcell_width = 1.0f / (float(num_samples));

    // init points to the canonical mutli jittered pattern
    for(int i = 0; i < sqrt_samples; i++) 
        for(int j = 0; j < sqrt_samples; j++) {
            samples[i+sqrt_samples+j].setX(i * sqrt_samples * subcell_width + 
                    j * subcell_width + rng() * subcell_width);
            samples[i+sqrt_samples+j].setY(j * sqrt_samples * subcell_width + 
                    i * subcell_width + rng() * subcell_width);
    }

    // shuffle x coords within each column any coords within each row
    for(int i = 0; i < sqrt_samples; i++)
        for(int j = 0; j < sqrt_samples; j++) {
            int k = j + int(rng() * (sqrt_samples - j - 1));
            float t = samples[i*sqrt_samples+j].x();
            samples[i*sqrt_samples+j].setX(samples[i*sqrt_samples+k].x());
            samples[i*sqrt_samples+k].setX(t);

            k = j + int(rng() * (sqrt_samples - j - 1));
            t = samples[j*sqrt_samples+i].y();
            samples[j*sqrt_samples+i].setY(samples[k*sqrt_samples+i].y());
            samples[k*sqrt_samples+i].setY(t);
        }
}

void shuffle(Vector2* samples, int num_samples) {
    for (int i = num_samples - 2; i >= 0; i--) {
        int target = int(rng() * (double)i);
        Vector2 temp = samples[i+1];
        samples[i+1] = samples[target];
        samples[target] = temp;
    }
}

void boxFilter(Vector2* samples, int num_samples) {
    for (int i = 0; i < num_samples; i++) {
        samples[i].setX(samples[i].x() - 0.5f);
        samples[i].setY(samples[i].y() - 0.5f);
    }
}

void tentFilter(Vector2* samples, int num_samples) {
    for (int i = 0; i < num_samples; i++) {
        float x = samples[i].x();
        float y = samples[i].y();

        if (x < 0.5f) samples[i].setX((float)sqrt(2.0f * (double)x) - 1.0f);
        else samples[i].setX(1.0f - (float)sqrt(2.0f - 2.0f * (double)x));

        if (y < 0.5f) samples[i].setY((float)sqrt(2.0f * (double)y) - 1.0f);
        else samples[i].setY(1.0f - (float)sqrt(2.0f - 2.0f * (double)y));
    }
}

void cubicSplineFilter(Vector2* samples, int num_samples) {
    for (int i = 0; i < num_samples; i++) {
        samples[i].setX(cubicFilter(samples[i].x()));
        samples[i].setY(cubicFilter(samples[i].y()));
    }
}

inline void random(float* samples, int num_samples) {
    for (int i = 0; i < num_samples; i++) samples[i] = rng();
}

inline void jitter(float* samples, int num_samples) {
    for (int i = 0; i < num_samples; i++) samples[i] = ((double)i + rng()) / (double)num_samples;
}

void shuffle(float* samples, int num_samples) {
    for (int i = num_samples - 2; i >= 0; i--) {
        int target = int(rng() * (double)i);
        float temp = samples[i+1];
        samples[i+1] = samples[target];
        samples[target] = temp;
    }
}

