#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "../entity.h"
#include "../../texturemanager.h"

struct Stats {
    int health;
    int maxHealth;
    int mana;
    int maxMana;
    float strength;
    float defense;
    float speed;
    float intelligence;
    float luck;
    float level;
};

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Player : public Entity {
    private:
        int textureIndex = 0;
        sf::Sprite sprite;
        sf::Vector2f position;
        sf::View view;
        TextureManager textureManager;
    public:
        Player(TextureManager *textureManager);
        ~Player();
        Stats stats;
        void update(int tick);
        void render(sf::RenderWindow* window);
        void setPosition(sf::Vector2f position);
        sf::View getView();
        sf::Vector2f getPosition();
        sf::Sprite getSprite();

        // Movement
        void move(Direction direction);
};

#endif