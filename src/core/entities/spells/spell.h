#include "../../level/level.h"
#ifndef SPELL_H
#define SPELL_H

#include <SFML/Graphics.hpp>

class Spell {
    private:
        int spellCost;

    public:
        Spell() {}
        ~Spell() {}
        virtual void render(sf::RenderWindow* window);
        virtual void update(int tick, Level level);
};

#endif