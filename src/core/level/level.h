#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include "../../modules/perlin.h"
#include "../entities/object.h"
#include <SFML/Graphics.hpp>

class Level {
    private:
        Perlin perlin;
        std::string atlasName;
        std::vector<int> atlasIndices;
        std::vector<Object> objects;
        int seed;

    public:
        Level(
            std::string atlasName,
            std::vector<int> atlasIndices,
            int seed);
        ~Level();

        void update(int tick);
        void render(sf::RenderWindow* window);
        void renderAt(sf::RenderWindow* window, sf::Vector2f position);
};
#endif