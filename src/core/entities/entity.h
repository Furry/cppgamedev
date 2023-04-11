#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

// #include "../level/level.h"

class Level;

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

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

class Entity {
    public:
        Entity() {};
        virtual void update(int tick, Level level) = 0;
        virtual void render(sf::RenderWindow* window) = 0;

        virtual void setPosition(sf::Vector2f position) = 0;
        virtual sf::Vector2f getPosition() = 0;

        //Movement
        virtual void pMove(Direction direction) = 0;
        virtual void eMove() = 0;

        //Attack
        virtual void attack() = 0;
        
        //Could create a random test to see if that's the case, but seems like it would take too much work....
        //Also player doesn't even have that for the movements
};
#endif