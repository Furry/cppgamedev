#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../entity.h"
#include "../../texturemanager.h"
#include "../../level/level.h"
#include "../player/player.h"

class Enemy : public Entity {
    private:
        int textureIndex = 0;
        sf::Sprite sprite;
        //sf::Vector2f position;
        TextureManager textureManager;
        Player player;
    public:
        Stats stats;
        sf::Vector2f position;
        void update(int tick, Level level) {};
        void render(sf::RenderWindow* window) {};
        void setPosition(sf::Vector2f position) {};
        int distance() {};
        sf::Sprite getSprite() {};
        sf::Vector2f getPosition() {};

        //Enemy movement
        void move() {};

        //Enemy atk
        void attack() {};
};
#endif