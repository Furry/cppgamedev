#include "level.h"
#include "../../modules/perlin.h"

Level::Level(std::string atlasName, std::vector<int> atlasIndices, sf::Vector2f viewPosition, int seed) {

    this->atlasIndices = atlasIndices;
    this->viewPosition = viewPosition;
    this->atlasName = atlasName;
    this->seed = seed;

    this->perlin = Perlin(
        seed, atlasIndices.size() - 1, 1.0
    );
}
