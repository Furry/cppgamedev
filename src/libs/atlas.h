// A class to define a texture atlas. An atlas is a collection of textures that are packed into a single asset/image.
// Given a texture size, the image is divided into a grid of cells. Each cell is a square of the given size.
#include <SFML/Graphics.hpp>
#include <vector>
#include <string.h>

#ifndef ATLAS_H
#define ATLAS_H

class Atlas {
    private:
        int width;
        int height;
        int entries;
        std::string location;
        sf::Image image;
    public:
        Atlas(std::string location, int width, int height);
        int getCount();
        sf::Texture* getTexture(int x, int y);
        sf::Texture* getTexture(int index);
};

#endif