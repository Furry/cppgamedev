#include <mutex>
#include <thread>
#include <hash_map>
#include <iostream>

#include "../libs/ticker.h"
// #include "entities/entity.h"
#include "entities/player/player.h"
#include "./texturemanager.h"

class Game {
    private: 
        std::thread *tickThread;
        bool isRemote = false;
        int tickCount = 0;
        int tickRate = 45; // hz
        // A hashmap of all entities
        std::map<std::string, Entity*> entities;

        TextureManager textureManager;
        // Player player;

    public:
        Player *player;
        Game(int seed) {
            // Create the tick thread, with a tick rate of 45 hz
            this->isRemote = false;
            TextureManager textureManager = TextureManager();
            Player player = Player(&textureManager);
        }

        void start() {
            // Spawn a thread that calls the tick function
            this->tickThread = new std::thread([this]() {
                while (true) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / this->tickRate));
                    tick();
                }
            });
        }

        TextureManager getTextureManager() {
            return this->textureManager;
        }

        void stop() {
            // Stop the tick thread
            this->tickThread->join();
        }

        void tick() {
            // Tick all entities
            // this->player->update(tickCount);
            for (auto &entity : this->entities) {
                // entity.second->update(tickCount);
            }
            tickCount++;
        }

        // Entity Methods //
        void addEntity(std::string name, Entity &entity) {
            this->entities[name] = &entity;
        }

        void removeEntity(std::string name) {
            // Remove an entity from the game
            this->entities.erase(name);
        }
};