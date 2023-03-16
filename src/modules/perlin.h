#ifndef PERLIN_H
#define PERLIN_H

class Perlin {
    private:
        // The seed for the noise.
        int seed;
        // From 0 to n, where n is the maximum value of the noise in a given spot.
        int bound;
        float intensity = 1.0;
    public:
        Perlin(int intensity);
        Perlin(int seed, int intensity);
        Perlin(int seed, int bound, float intensity);

        int getNoise(int x, int y);
};

#endif