#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <map>
#include <string>
#include <SFML/Graphics.hpp>

#include "../libs/atlas.h"

class TextureManager {
    private:
        std::unordered_map<std::string, std::unordered_map<int, sf::Texture*>> *textures;
    public:
        TextureManager();
        ~TextureManager();

        void load(std::string name, int width, int height);
        sf::Texture* getTexture(std::string name, int index);
};
#endif
