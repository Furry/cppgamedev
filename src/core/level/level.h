#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include "../../modules/perlin.h"

#include <SFML/Graphics.hpp>

class Level {
    private:
        Perlin perlin;
        std::string atlasName;
        std::vector<int> atlasIndices;
        sf::Vector2f viewPosition;
        int seed;

    public:
        Level(
            std::string atlasName,
            std::vector<int> atlasIndices,
            sf::Vector2f viewPosition,
            int seed);
        ~Level();

        void update(int tick);
        void render(sf::RenderWindow* window);
        void setViewPosition(sf::Vector2f position);
        sf::Vector2f getViewPosition();
};
#endif