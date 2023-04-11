#include "level.h"
#include "../../modules/perlin.h"
#include "../entities/entity.h"
#include "../entities/player/player.h"
#include "../texturemanager.h"
#include "../entities/enemy/ghost.cpp"
#include "../entities/enemy/enemy.h"

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
            for (int i = 0; i < enemies.size(); i++) {
                //entities[i]->render(window);
                enemies[i]->render(window);
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
            for (int i = 0; i < enemies.size(); i++) {
                //entities[i]->update(tick, *this);
                enemies[i]->update(tick, *this);
            }
        }


        //When updating I should probably be checking if there are enough enemies and if there isn't
        //then I can just create more enemies 
        void updateEnemies(int tick, TextureManager m, sf::RenderWindow* window) {
            // Print size of entities
            for (int i = 0; i < entities.size(); i++) {
                entities[i]->update(tick, *this);
            }

            
            spawnEnemies(m, window, tick);
            render(window);
        }

        void spawnEnemies(TextureManager m, sf::RenderWindow* window, int tick) {

            //Creates enemies while this is under the cap of enemies that should be near the player
            while( enemies.size() < 2) {
                int enemySelection = (1 + rand() % 2);
                float x = player.getPosition().x + rand() % 500;
                float y = player.getPosition().y + random() % 500;
                sf::Vector2f enemyPos = sf::Vector2f(x, y);
                switch (enemySelection) {
                    case 1: {
                        Ghost *g = new Ghost(&m);
                        g->setPosition(enemyPos);
                        g->render(window);
                        //g->update(tick, *this);
                        addEnemies(g);
                        break; 
                    }
                    case 2: 
                        //Create another enemy class here for later.
                        int x = 4;
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