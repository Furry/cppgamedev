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
            this->stats = {20, 20, 100, 100, 1, 1, 3, 1, 1, 1};
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

            int currentHealth = this->stats.health;
            int maxHealth = this->stats.maxHealth;
            
            int xpos = this->position.x;
            int ypos = this->position.y;

            float healthPercent = static_cast<float>(currentHealth) / maxHealth;

            sf::Vector2f healthBarSize(75, 6);

            sf::RectangleShape healthBarOuter(healthBarSize + sf::Vector2f(2, 2));
            healthBarOuter.setFillColor(sf::Color::Transparent);
            healthBarOuter.setOutlineColor(sf::Color::Black);
            healthBarOuter.setOutlineThickness(1);
            healthBarOuter.setPosition(xpos - healthBarSize.x / 2, ypos + 55);

            sf::RectangleShape healthBar(healthBarSize);
            healthBar.setFillColor(sf::Color::Red);
            healthBar.setSize(sf::Vector2f(healthBarSize.x * healthPercent, healthBarSize.y));
            healthBar.setPosition(xpos - healthBarSize.x / 2 + 1, ypos + 55 + 1);

            sf::Text healthText;    
            healthText.setString(std::to_string(static_cast<int>(healthPercent * 100)) + "%");
            healthText.setCharacterSize(10);
            healthText.setFillColor(sf::Color::White);
            healthText.setPosition(xpos - healthText.getLocalBounds().width / 2, ypos + 50 + 2);

            window->draw(healthBarOuter);
            window->draw(healthBar);
            window->draw(healthText);
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

            if( distance() < 5 && tick % 20 == 0){ //Enemy attacks if the player distance is less than 10 & module 10 tick
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