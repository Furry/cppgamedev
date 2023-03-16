

#include <string>
#include <SFML/Graphics.hpp>
#include "atlas.h"

Atlas::Atlas(std::string location, int width, int height) {
    this->location = location;
    this->width = width;
    this->height = height;
    this->image = sf::Image();

    // Load the image
    image.loadFromFile(location);

    // Calculate the number of entries
    entries = (image.getSize().x / width) * (image.getSize().y / height);
}

sf::Texture* Atlas::getTexture(int x, int y) {
    // Create a new sf::Texture object
    sf::Texture* texture = new sf::Texture();

    // Create a new sf::Image object to store the sub-image
    sf::Image subImage;

    // Copy the portion of the atlas image to the subImage
    subImage.create(width, height);
    subImage.copy(image, 0, 0, sf::IntRect(x, y, width, height));

    // Load the subImage into the texture
    texture->loadFromImage(subImage);

    // Return the pointer to the new texture
    return texture;
}

sf::Texture* Atlas::getTexture(int i) {
    // Calculate how many columns there are
    int columns = image.getSize().x / width;

    // Calculate the x and y coordinates of the texture
    int x = (i % columns) * width;
    int y = (i / columns) * height;

    // Get the texture
    return getTexture(x, y);
}

int Atlas::getCount() {
    return entries;
}