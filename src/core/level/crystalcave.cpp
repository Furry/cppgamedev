#include "level.h"
#include "../../modules/perlin.h"
#include "../entities/entity.h"
#include "../entities/player/player.h"
#include "../texturemanager.h"
#include "../entities/enemy/ghost.cpp"
#include "../entities/enemy/golem.cpp"
#include "../entities/enemy/enemy.h"
#include "../entities/spells/spell.h"
#include "../entities/spells/nova.cpp"

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
        std::vector<Spell*> spells;

        Player &player;
        int seed;
    public:
        TextureManager *textureManager;

        CrystalCave(int seed, Player *player) : player(*player) {
            this->seed = seed;
            this->player = *player;
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
                //enemies[i]->randomHeaderTest();
                //enemies[i]->move();
            }

            // Render spells
            for (int i = 0; i < spells.size(); i++) {
                spells[i]->render(window);
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

        void addSpells(Spell *spell){
            this->spells.push_back(spell);
        }

        void start() {
            this->tickThread = new std::thread([this]() {
                int tick = 0;
                while (true) {
                    this->update(tick);
                    tick++;
                    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 45));
                }
            });
        }


        void update(int tick){
            // Print size of entities
            for (int i = 0; i < enemies.size(); i++) {
                //entities[i]->update(tick, *this);
                enemies[i]->update(tick, *this);
            }

            for (int i = 0; i < spells.size(); i++) {
                if (spells[i]->isDead()) {
                    spells.erase(spells.begin() + i);
                } else {

                    // Check if there's an enemy in the spell's radius
                    for (int j = 0; j < enemies.size(); j++) {
                        Enemy *enemy = enemies[j];
                        // Get the center of the enemy via sprite size
                        sf::Vector2f pos = enemy->getPosition();
                        // Add half of it's width and height to get the center
                        pos.x += enemy->getSprite().getGlobalBounds().width / 2;
                        pos.y += enemy->getSprite().getGlobalBounds().height / 2;

                        if (spells[i]->doesCollide(pos)) {
                            enemy->stats.health -= 1;
                            if (enemy->stats.health <= 0) {
                                this->player.pts += 1;
                                enemies.erase(enemies.begin() + j);
                            }
                        }
                    }
                    spells[i]->update(tick, *this);
                }
                spells[i]->update(tick, *this);
            }
        }


        //When updating I should probably be checking if there are enough enemies and if there isn't
        //then I can just create more enemies 
        void updateEnemies(int tick, TextureManager m, sf::RenderWindow* window) {
            // Print size of entities
            /**
            for (int i = 0; i < entities.size(); i++) {
                entities[i]->update(tick, *this);
            }*/

            //std::cout << "Is this even working after the 1st run through of it " << std::endl;

            spawnEnemies(m, window, tick);
            update(tick);
            enemyAI(tick);
            render(window);

            
        }


        //Maybe a parameter needs to be called even if it has nothing to do w/ the functions inside of it 
        //so it doesn't fall out of scope or something like that ????
        void enemyAI(int tick){

            //From the tests done on this so far, I've determined that the loop works and there's definitely something going on 
            //because the print functions work, but whenever I try to call a function to one of the enemies[i], then it doesn't work
            //and nothing is called when the function is meant to be called ??? Idky the print func isn't working or the function in general.
            //Sobbing, I hate working on code at almost 3am, I should've gotten tipsy and slammed energy drinks altho they do nothing anymore.


            //std::cout << "Is the enemy AI actually trying to call something or does it do jackshit" << std::endl;
            for(int i = 0; i < enemies.size(); i++){
                //std::cout << "Loop function somehow worked" << std::endl;
                enemies[i]->eMove();
                //std::cout << "This broke before attack" << std::endl;
                enemies[i]->attack();

                //enemies[i]->randomHeaderTest(*this);
            }
        }

        void spawnEnemies(TextureManager m, sf::RenderWindow* window, int tick) {

            //Creates enemies while this is under the cap of enemies that should be near the player
            while( enemies.size() < 2) {
                int enemySelection = (1 + rand() % 2);
                float x = player.getPosition().x + ( (rand() % 350) * (-1 + rand() % 2) );    //Need to add a negative random maybe ( -1 + rand() % 2)
                float y = player.getPosition().y + ( (rand() % 350) * (-1 + rand() % 2) );  //Need to add a negative random maybe ( -1 + rand() % 2)
                sf::Vector2f enemyPos = sf::Vector2f(x, y);
                switch (enemySelection) {
                    case 1: {
                        Ghost *g = new Ghost(&m, &this->player);
                        g->setPosition(enemyPos);
                        g->render(window);
                        //g->update(tick, *this);
                        addEnemies(g);
                        break; 
                    }
                    case 2: 
                        //Create another enemy class here for later.
                        Golem *go = new Golem(&m, &this->player);
                        go->setPosition(enemyPos);
                        go->render(window);
                        //g->update(tick, *this);
                        addEnemies(go);
                        break; 
                }

            }



        }

        void stop() {
            this->tickThread->join();
        }

        Player& getPlayer() {
            return this->player;
        }

        std::vector<Enemy*> getEnemies() {
            return this->enemies;
        }

        std::vector<Spell*> getSpells() {
            return this->spells;
        }

        void nova(sf::Vector2f position) {
            Nova *n = new Nova(position);
            //this->spells.push_back(n);
            addSpells(n);
        }
};