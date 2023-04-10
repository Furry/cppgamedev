#include "level.h"
#include "../../modules/perlin.h"
#include "../entities/entity.h"
#include "../entities/player/player.h"
#include "../texturemanager.h"
#include "../entities/enemy/ghost.cpp"

// Class CrystalCave inherits from Level
class CrystalCave : public Level {
    private:
        std::thread *tickThread;
        Perlin perlin;
        std::string atlasName;
        std::vector<int> atlasIndices;
        std::vector<Object> objects;
        std::vector<Entity*> entities;
        std::vector<Enemy*> enemies;
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

        void render(sf::RenderWindow* window) {
            //Do nothing 
            //This is just for testing
            for (int i = 0; i < entities.size(); i++) {
                entities[i]->render(window);
            }
        }

        void renderAt(sf::RenderWindow* window, sf::Vector2f position);

        void addEntity(Entity *entity) {
            this->entities.push_back(entity);
            //When creating a new enemy, set its coordinates to randomly be within a 50 block radius of the player
        }

        void addEnemies(Enemy *enemy){
            this->enemies.push_back(enemy);
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


        void update(int tick){
            // Print size of entities
            for (int i = 0; i < entities.size(); i++) {
                entities[i]->update(tick, *this);
            }
        }


        //When updating I should probably be checking if there are enough enemies and if there isn't
        //then I can just create more enemies 
        void updateEnemies(int tick, TextureManager* m, sf::RenderWindow* window) {
            // Print size of entities
            for (int i = 0; i < entities.size(); i++) {
                entities[i]->update(tick, *this);
            }
            spawnEnemies(m);
            render(window);
        }

        void spawnEnemies(TextureManager* m) {

            //Creates enemies while this is under the cap of enemies that should be near the player
            while( enemies.size() < 2) {
                int enemySelection = (1 + rand() % 2);
                switch (enemySelection) {
                    case 1: {
                        Ghost g = Ghost(m);
                        break; 
                    }
                    case 2: 
                        int x = 4;  //Placeholder
                }

            }



        }

        void stop() {
            this->tickThread->join();
        }

        Player& getPlayer() {
            return this->player;
        }
};