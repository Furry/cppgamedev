#include <cmath>
#include <cstdlib>
#include <ctime>
#include "perlin.h"

Perlin::Perlin(int bound) {
    seed = time(NULL);
    this->bound = bound;
    this->intensity = 1.0;
}

Perlin::Perlin(int seed, int bound) {
    this->seed = seed;
    this->bound = bound;
    this->intensity = 1.0;
}

Perlin::Perlin(int seed, int bound, float intensity) {
    this->seed = seed;
    this->bound = bound;
    this->intensity = intensity;
}

int Perlin::getNoise(int x, int y) {
    srand(seed);

    int n = x + y * 57;
    n = (n << 13) ^ n;
    int nn = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;

    // Use an exponential distribution to make higher numbers rarer
    double uniform_random = (double)nn / 0x7fffffff;
    double exponential_random = -log(1.0 - uniform_random) / this->intensity;

    // Clamp the value to the range [0, bound]
    int result = static_cast<int>(round(exponential_random));
    return result > bound ? bound : result;
}