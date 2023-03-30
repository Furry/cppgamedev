#include "level.h"
#include "../../modules/perlin.h"

Level::Level(std::string atlasName, std::vector<int> atlasIndices, int seed) {

    this->atlasIndices = atlasIndices;
    this->atlasName = atlasName;
    this->seed = seed;

    this->perlin = Perlin(
        seed, atlasIndices.size() - 1, 1.0
    );

    this->objects = std::vector<Object>();
}

void Level::renderAt(sf::RenderWindow* window, sf::Vector2f position) {

}