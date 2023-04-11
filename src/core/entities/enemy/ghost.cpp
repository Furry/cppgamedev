#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "enemy.h"
#include "../player/player.h"
#include "../../level/level.h"
//#include "../../level/crystalcave.cpp"



class Ghost : public Enemy {
    private:
        int id;
        sf::Sprite sprite;
        TextureManager textureManager;
        Player player;
    public:
        Ghost(TextureManager *textureManager, Player &player) {
            std::cout << "Ghost created" << std::endl;
            id = rand() % 1000;
            this->textureManager = *textureManager;
            this->sprite = sf::Sprite();
            this->sprite.setScale(5,5);
            this->stats = {20, 20, 100, 100, 1, 1, 4, 1, 1, 1};
            this->player = player;
            //this->sprite.setTexture(*this->textureManager.getTexture("lofiChar", 15));
        }
        ~Ghost() {
            std::cout << "Ghost destroyed" << std::endl;
        }
        
        //For some reason this doesn't like me getting player from level, so I need to figure out why the reference
        //point isn't working out.
        //Initially fixed it w/ Level& level, not working now tho....
        void update(int tick, Level level){ 
            //std::cout << "Setting texture for the ghost as demo" << std::endl; //this is working just fine, and is being called
            //even in main and for the crystalcave.cpp
            //this->player = level.getPlayer(); //I was trying to access the pointer to player through the level.h
            //but it didn't work so I just decide to declare it within the levels itself.
            this->sprite.setTexture(*this->textureManager.getTexture("lofiChar", 31));
        }

        void setPosition(sf::Vector2f position) {
            this->position = position;
            this->sprite.setPosition(position);
        }

        void render(sf::RenderWindow* window) {
            //std::cout << "Ghost is rendering" << std::endl;
            this->sprite.setPosition(this->position);
            window->draw(this->sprite);
        }

        int distance() {
            int xPlayerEnemyDist = this->position.x - this->player.getPosition().x;
            int yPlayerEnemyDist = this->position.y - this->player.getPosition().y;
            int playerEnemyDist = sqrt( (xPlayerEnemyDist)^2 + (yPlayerEnemyDist)^2 );
            return playerEnemyDist;
        }

        void move() {
            //Why isn't this working when its being called for ???
            std::cout << "Ghost is doing something to try to move" << std::endl;
            //Enemy x coordinate movement in accordinate to player x pos
            if( this->position.x < player.getPosition().x ) {
                this->position.x += this->stats.speed;

            }
            else if( this->position.x > player.getPosition().x ) {
                this->position.x -= this->stats.speed;
            }//Should be an else here but it'll do nothing as the playere & enemy x coordinates match and no movement needs to be done
            

            //Enemy y coordinate movement in accordance to player y pos
            if( this->position.y < player.getPosition().y ) {
                this->position.y += this->stats.speed;

            }
            else if( this->position.y > player.getPosition().y ) {
                this->position.y -= this->stats.speed;
            }//Should be an else here but it'll do nothing as the playere & enemy y coordinates match and no movement needs to be done
            
        }

        //Why isn't this working even when I have something that should be keeping it in scope ???
        //It also has a parameter so that shouldn't be the issue...... Why does only update & render work ? 
        //Maybe cuz entity.h has both of them ???
        void randomHeaderTest(Level level){
            std::cout << "This was in the header and seems to be working" << std::endl;
        }


        void attack(){

            std::cout << "Ghost is activating the atk function" << std::endl;

            float def = player.stats.defense;
            int dmgRed = def / def + 100; //Damage reduction formula
            float luck = player.stats.luck;

            if( distance() < 3){
                std::cout << "Ghost is within reach to atk the player and is currently trying to atk them" << std::endl;
                if( (1 + rand() % 20) < luck) { //If player's luck is greater than they dodge the atk
                    int dmg = dmgRed * this->stats.strength;
                    player.stats.health -= dmg;
                }
            }
            
        }

        sf::Sprite getSprite() {
            return this->sprite;
        }

        sf::Vector2f getPosition() {
            return this->position;
        }
};