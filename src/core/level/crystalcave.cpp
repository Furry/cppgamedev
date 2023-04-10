#include "level.h"
#include "../../modules/perlin.h"
#include "../entities/entity.h"
#include "../entities/player/player.h"
#include "../texturemanager.h"

// Class CrystalCave inherits from Level
class CrystalCave : public Level {
    private:
        std::thread *tickThread;
        Perlin perlin;
        std::string atlasName;
        std::vector<int> atlasIndices;
        std::vector<Object> objects;
        std::vector<Entity*> entities;
        Player &player;
        int seed;
    public:
        TextureManager *textureManager;

        CrystalCave(int seed, Player &player) : player(player) {
            this->seed = seed;
            this->player = player;
            this->perlin = Perlin(seed);
            this->atlasName = "crystalCaveObjects8x8";
            this->atlasIndices = {165, 166, 167, 168, 169};
            this->textureManager = new TextureManager();
        }

        void render(sf::RenderWindow* window);
        void renderAt(sf::RenderWindow* window, sf::Vector2f position);

        void addEntity(Entity *entity) {
            this->entities.push_back(entity);
        }

        void start() {
            this->tickThread = new std::thread([this]() {
                int tick = 0;
                while (true) {
                    this->update(tick);
                    tick++;
                }
            });
        }

        void update(int tick) {
            // Print size of entities
            for (int i = 0; i < entities.size(); i++) {
                entities[i]->update(tick, *this);
            }
        }

        void stop() {
            this->tickThread->join();
        }

        Player& getPlayer() {
            return this->player;
        }
};