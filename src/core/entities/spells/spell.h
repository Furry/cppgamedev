
#ifndef SPELL_H
#define SPELL_H

#include <SFML/Graphics.hpp>

#include "../../level/level.h"

class Spell {
    private:
        int spellCost;
        //Level level;
    public:
        Spell(sf::Vector2f position);
        Spell() {};
        ~Spell() {};
        virtual void render(sf::RenderWindow* window) = 0;
        virtual void update(int tick, Level level) = 0;
        virtual bool isDead() = 0;
};

#endif