#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <vector>
#include <thread>
#include <iostream>

#include "../../modules/perlin.h"
#include "../entities/object.h"
#include "../entities/entity.h"
// #include "../entities/player/player.h"

#include <SFML/Graphics.hpp>

class Player;


//Implement enemy spawning w/ random
//Add a cap to the amount of enemies
//A spawn radius around the player for the enemy spawns
//If there's below x amt of enemies then automatically spawn them w/o waiting for random check

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

        Player getPlayer();
};
#endif