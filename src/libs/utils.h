#ifndef _UTILS_H
#define _UTILS_H

#include <SFML/Graphics.hpp>

sf::Vector2f getPositionInBound(float minx, float maxx, float miny, float maxy) {
    // Initialize random seed
    std::srand(std::time(nullptr));

    // Generate random position within the specified bounds
    float x = minx + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (maxx - minx)));
    float y = miny + static_cast<float>(std::rand()) / (static_cast<float>(RAND_MAX / (maxy - miny)));

    return sf::Vector2f(x, y);
}

#endif