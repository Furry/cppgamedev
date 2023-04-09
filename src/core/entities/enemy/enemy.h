#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../entity.h"
#include "../../texturemanager.h"
#include "../../level/level.h"

class Enemy : public Entity {
    private:
        int textureIndex = 0;
        sf::Sprite sprite;
        sf::Vector2f position;
        TextureManager textureManager;
    public:
        Stats stats;
        virtual void update(int tick, Level level) {};
        void render(sf::RenderWindow* window) {};
        void setPosition(sf::Vector2f position) {};
        sf::Sprite getSprite() {};
        sf::View getView();
        sf::Vector2f getPosition() {};
};
#endif