#pragma once

#include <SFML/Graphics.hpp>
#include "./spell.h"
#include "../../level/level.h"

class Nova : public Spell {
    private:
        int spellCost;
        int ticksAlive;
        int ticksToLive;
        sf::Vector2f position;
        sf::CircleShape explosion;
        float scaleFactor;

    public:
        Nova(sf::Vector2f position);
        ~Nova();

        void render(sf::RenderWindow* window);
        bool isDead();
        void update(int tick, Level &level);
        bool doesCollide(sf::Vector2f position);
};
