#include "level.h"
#include "../../modules/perlin.h"
#include "../entities/entity.h"
#include "../entities/player/player.h"
#include "../texturemanager.h"
//#include "../entities/enemy/ghost.cpp"
//#include "../entities/enemy/golem.cpp"
#include "../entities/enemy/enemy.h"
#include "../entities/spells/spell.h"
//#include "../entities/spells/nova.cpp"

#include <iostream>
#include <fstream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "../../libs/atlas.h"


#include "../../libs/ticker.h"
#include "../../libs/layerreader.h"


#include <sstream>

using namespace std;

//Class Hell inherits from Level.h

class Hell : public Level { 
    private:
        std::thread *tickThread;
        Perlin perlin;  //Perlin isn't being used anymore so what's the point of this being included still
        std::string atlasName;
        std::vector<int> atlasIndices;
        std::vector<Object> objects;
        std::vector<Entity*> entities;
        std::vector<Enemy*> enemies;
        std::vector<Spell*> spells;

        Player &player;
        int seed;   //Is this even needed anymore considering Perlin isn't being used ? 

    public: 
        TextureManager *textureManager;

        Hell(int seed, Player *player) : player(*player) {
            
            this->player = *player;
        }


        void renderMap(sf::Sprite sprite, sf::RenderWindow* window, TextureManager m) {

            sf::Image image;
            image.loadFromFile("static/levels/spirit/layer1.png");
            sf::Vector2u size = image.getSize();
            sf::Color color;

            LayerReader layerReader = LayerReader("static/levels/spirit/layer1.txt");

            // Loop through each pixel in the image
            for (int i = 0; i < size.x; i++) {
                for (int j = 0; j < size.y; j++) {
                    // Print the RGB
                    color = image.getPixel(i, j);
                    int index = layerReader.getTile(color.r, color.g, color.b, color.a);
                    if (index != -1) {
                        sprite.setPosition(i * 32, j * 32);
                        sprite.setTexture(
                            *m.getTexture("parasiteDenObjects8x8", layerReader.getTile(color.r, color.g, color.b, color.a)));
                        window->draw(sprite);
                    }
                }
            }
        }

        void render(sf::RenderWindow* window);

        void renderAt(sf::RenderWindow* window, sf::Vector2f position);

        void start();

        void update(int tick);

        void stop();

        void addEnemies();

        void spawnEnemies();

        void clearEnemies() {
            enemies.clear();
        }
    
        void addSpell(Spell *spell);

        void nova(sf::Vector2f position);

        void damageInRadius(sf::Vector2f position, int radius, int damage);

        Player getPlayer();
};