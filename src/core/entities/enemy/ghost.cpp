#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "enemy.h"
#include "../player/player.h"
#include "../../level/level.h"


class Ghost : public Enemy {
    private:
        int id;
        sf::Sprite sprite;
        TextureManager textureManager;
        Player &player;
        int tick;
    public:
        Ghost(TextureManager *textureManager, Player* player) : player(*player) {
            id = rand() % 1000;
            this->textureManager = *textureManager;
            this->sprite = sf::Sprite();
            this->sprite.setScale(5,5);
            this->stats = {20, 20, 100, 100, 1, 1, 4, 1, 1, 1};
            this->player = *player;
        }
        ~Ghost() {
            this->player.pts += 1;
        }
        
        void update(int tick, Level level){ 
            this->sprite.setTexture(*this->textureManager.getTexture("chars8x8dEncounters", 350));  //I wonder if I can put this in the constructor
            this->tick = tick;

            //Maybe implement something here to see if the enemies health is 0, and if it is then deconstruct the class
            if( this->stats.health == 0){
                delete this;
            }
        }

        void setPosition(sf::Vector2f position) {
            //Setting the position of the sprite when its drawn.
            this->position = position;
            this->sprite.setPosition(position);
        }

        void render(sf::RenderWindow* window) {
            //std::cout << "Ghost is rendering" << std::endl;
            this->sprite.setPosition(this->position);
            window->draw(this->sprite);

            //Enemy hp bar
            sf::RectangleShape healthBar;
            healthBar.setSize(sf::Vector2f(100, 10));
            healthBar.setFillColor(sf::Color::Red);
            healthBar.setPosition(this->position.x - 50, this->position.y - 50);
            window->draw(healthBar);
        }

        int distance() {
            sf::Vector2f playerPos = this->player.getPosition();
            sf::Vector2f enemyPos = this->position;

            float deltaX = playerPos.x - enemyPos.x;
            float deltaY = playerPos.y - enemyPos.y;

            return std::sqrt(deltaX * deltaX + deltaY * deltaY);
        }

        void pMove(Direction direction) {};

        void eMove(){
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
            float dmgRed = def / (def + 100); //Damage reduction formula
            float luck = player.stats.luck;

            if( distance() < 10 && tick % 10 == 0){ //Enemy attacks if the player distance is less than 10 & module 10 tick
                if( (1 + rand() % 30) > luck) { //If player's luck is greater than they dodge the atk, max player luck is 20
                    float dmg = dmgRed * this->stats.strength;
                    if(dmg < 1){
                        dmg = 1;
                    }
                    this->player.stats.health -= dmg;
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