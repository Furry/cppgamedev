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
    // TextureMap texturesTemp = TextureMap();

    // Create a map for the textures
    std::unordered_map<int, sf::Texture*> textureMap = std::unordered_map<int, sf::Texture*>();

    // test.insert_or_assign("test", std::map<int, int>());
    // Loop through the atlas and add the textures to the map
    for (int i = 0; i < atlas->getCount(); i++) {
        textureMap[i] = atlas->getTexture(i);
    }

    this->textures->insert(std::make_pair(name, textureMap));
}

sf::Texture* TextureManager::getTexture(std::string name, int index) {
    // Get the texture from the map
    return this->textures->at(name).at(index);
}