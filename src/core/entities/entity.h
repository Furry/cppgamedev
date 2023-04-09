#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

// #include "../level/level.h"
class Level;

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
};
#endif