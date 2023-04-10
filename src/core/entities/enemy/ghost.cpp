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
        Ghost(TextureManager *textureManager) {
            std::cout << "Ghost created" << std::endl;
            id = rand() % 1000;
            //this->stats = {20, 20, 100, 100, 1, 1, 1, 1, 1, 1}
        }
        ~Ghost() {
            std::cout << "Ghost destroyed" << std::endl;
        }
        
        //For some reason this doesn't like me getting player from level, so I need to figure out why the reference
        //point isn't working out.
        void update(int tick, Level& level){
            this->player = level.getPlayer();
            std::cout << "Setting texture for the ghost as demo" << std::endl;
            this->sprite.setTexture(*this->textureManager.getTexture("lofiChar", 15));
        }

        void setPosition(sf::Vector2f position) {
            this->position = position;
            this->sprite.setPosition(position);
        }

        void render(sf::RenderWindow* window) {
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


        void attack(){

            float def = player.stats.defense;
            int dmgRed = def / def + 100; //Damage reduction formula
            float luck = player.stats.luck;

            if( distance() < 3){
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