#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../entity.h"
#include "../../texturemanager.h"

class Player : public Entity {
    private:
        int textureIndex = 0;
        sf::Sprite sprite;
        sf::Vector2f position;
        TextureManager textureManager;
    public:
        Player(TextureManager textureManager);
        ~Player();
        void update(int tick);
        void render(sf::RenderWindow* window);
        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition();
        sf::Sprite getSprite();
};

#endif