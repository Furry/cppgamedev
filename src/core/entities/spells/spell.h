
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
        void render(sf::RenderWindow* window);
        virtual void update(int tick, Level level) = 0;
};

#endif