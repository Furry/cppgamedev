#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <thread>
#include <iostream>

#include "../../modules/perlin.h"
#include "../entities/object.h"
#include "../entities/entity.h"
#include "../entities/spells/spell.h"

// #include "../entities/player/player.h"

#include <SFML/Graphics.hpp>

class Player;
class Spell;

class Level {
    private:
        std::thread *tickThread;
        Perlin perlin;
        std::string atlasName;
        std::vector<int> atlasIndices;
        std::vector<Object> objects;
        // std::vector<Entity*> entities;
        Player* player;
        int seed;

    public:
        Level() {};
        void render(sf::RenderWindow* window);
        void renderAt(sf::RenderWindow* window, sf::Vector2f position);
        void start();
        void update(int tick);
        void stop();
        void addEnemies();
        void spawnEnemies();
    
        void addSpell(Spell *spell);
        void nova(sf::Vector2f position);
        Player getPlayer();
};
#endif