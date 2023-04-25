#include <map>
#include <string>
#include <SFML/Graphics.hpp>

#include "../libs/atlas.h"
#include "./texturemanager.h"

#include <iostream>

#define TextureMap std::unordered_map<std::string, std::unordered_map<int, sf::Texture*>>
TextureManager::TextureManager() {
    // By pointer
    this->textures = new std::unordered_map<std::string, std::unordered_map<int, sf::Texture*>>();
}

TextureManager::~TextureManager() {
    // Clean up uwu
    // delete this->textures;
}

void TextureManager::load(std::string name, int width, int height) {
    // Load the atlas
    Atlas* atlas = new Atlas("static/textures/" + name + ".png", width, height);

    // Create a map for the textures and texture rects
    std::unordered_map<int, sf::Texture*> textureMap = std::unordered_map<int, sf::Texture*>();
    std::unordered_map<int, sf::IntRect> textureRectMap = std::unordered_map<int, sf::IntRect>();

    // Loop through the atlas and add the textures and texture rects to their respective maps
    for (int i = 0; i < atlas->getCount(); i++) {
        textureMap[i] = atlas->getTexture(i);
    }

    this->textures->insert(std::make_pair(name, textureMap));
    std::cout << "Loaded " << name << " with " << atlas->getCount() << " textures" << std::endl;
}

sf::Texture* TextureManager::getTexture(std::string name, int index) {
    // Get the texture from the map
    return this->textures->at(name).at(index);
}