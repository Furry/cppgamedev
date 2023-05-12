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
#include "../entities/npc/dungeonKeeper.cpp"

#include <iostream>
#include <fstream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "../../libs/atlas.h"


#include "../../libs/ticker.h"
#include "../../libs/layerreader.h"


#include <sstream>

using namespace std;

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
        //DungeonKeeper &dungeonKeeper;
        int seed;
    public:
        TextureManager *textureManager;
        DungeonKeeper dungeonKeeper;

        CrystalCave(int seed, Player *player) : player(*player), dungeonKeeper(dungeonKeeper) {
            this->seed = seed;
            this->player = *player;
            this->perlin = Perlin(seed);
            this->atlasName = "crystalCaveObjects8x8";
            this->atlasIndices = {165, 166, 167, 168, 169};
            this->textureManager = new TextureManager();
        }

        void renderMap(sf::Sprite sprite, sf::RenderWindow* window, TextureManager m) {

            sf::Image image;
            image.loadFromFile("static/levels/crystalcave/crystalcave.png");
            sf::Vector2u size = image.getSize();
            sf::Color color;

            LayerReader layerReader = LayerReader("static/levels/crystalcave/crystalcave.txt");

            // Loop through each pixel in the image
            for (int i = 0; i < size.x; i++) {
                for (int j = 0; j < size.y; j++) {
                    // Print the RGB
                    color = image.getPixel(i, j);
                    int index = layerReader.getTile(color.r, color.g, color.b, color.a);
                    if (index != -1) {
                        sprite.setPosition(i * 32, j * 32);
                        sprite.setTexture( *m.getTexture("crystalCaveObjects8x8", layerReader.getTile(color.r, color.g, color.b, color.a)));
                        window->draw(sprite);
                    }
                }
            }
            
            this->dungeonKeeper = DungeonKeeper(&m);

            float x = 200;
            float y = 200;
            sf::Vector2f keeperPos = sf::Vector2f(x, y);
            this->dungeonKeeper.setPosition( keeperPos );
        }

        void render(sf::RenderWindow* window) {
            for (int i = 0; i < enemies.size(); i++) {
                //entities[i]->render(window);
                enemies[i]->render(window);
            }

            // Render spells
            for (int i = 0; i < spells.size(); i++) {
                spells[i]->render(window);
            }

            this->dungeonKeeper.render(window);

        }

        void renderAt(sf::RenderWindow* window, sf::Vector2f position);

        void addEntity(Entity *entity) {
            this->entities.push_back(entity);
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

            this->dungeonKeeper.updatePlayerPos( this->player.getPosition() );
        }


        //When updating I should probably be checking if there are enough enemies and if there isn't
        //then I can just create more enemies 
        void updateEnemies(int tick, TextureManager m, sf::RenderWindow* window) {

            spawnEnemies(m, window, tick);
            update(tick);
            enemyAI(tick);
            render(window);

        }


        void enemyAI(int tick){

            for(int i = 0; i < enemies.size(); i++){
                enemies[i]->eMove();
                enemies[i]->attack();
            }
        }

        void spawnEnemies(TextureManager m, sf::RenderWindow* window, int tick) {

            //Creates enemies while this is under the cap of enemies that should be near the player
            if(tick > 300) {
                while( enemies.size() < 2) {
                    int enemySelection = (1 + rand() % 2);
                    float x = player.getPosition().x + ( (rand() % 350) * (-1 + rand() % 2) );    
                    float y = player.getPosition().y + ( (rand() % 350) * (-1 + rand() % 2) );  
                    sf::Vector2f enemyPos = sf::Vector2f(x, y);
                    switch (enemySelection) {
                        case 1: {
                            Ghost *g = new Ghost(&m, &this->player);
                            g->setPosition(enemyPos);
                            g->render(window);
                            addEnemies(g);
                            break; 
                        }
                        case 2: 
                            //Create another enemy class here for later.
                            Golem *go = new Golem(&m, &this->player);
                            go->setPosition(enemyPos);
                            go->render(window);
                            addEnemies(go);
                            break; 
                    }

                }
            }



        }

        void clearEnemies() {
            enemies.clear();
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
            addSpells(n);
        }
};