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
        Player &player;
    public:
        Ghost(TextureManager *textureManager, Player* player) : player(*player) {
            std::cout << "Ghost created" << std::endl;
            id = rand() % 1000;
            this->textureManager = *textureManager;
            this->sprite = sf::Sprite();
            this->sprite.setScale(5,5);
            this->stats = {20, 20, 100, 100, 1, 1, 4, 1, 1, 1};
            this->player = *player;
        }
        ~Ghost() {
            std::cout << "Ghost destroyed" << std::endl;
            this->player.pts += 1;
        }
        
        //For some reason this doesn't like me getting player from level, so I need to figure out why the reference
        //point isn't working out.
        //Initially fixed it w/ Level& level, not working now tho....
        void update(int tick, Level level){ 
            //std::cout << "Setting texture for the ghost as demo" << std::endl; //this is working just fine, and is being called
            //even in main and for the crystalcave.cpp
            //this->player = level.getPlayer(); //I was trying to access the pointer to player through the level.h
            //but it didn't work so I just decide to declare it within the levels itself.
            //this->sprite.setTexture(*this->textureManager.getTexture("lofiChar", 31));
            this->sprite.setTexture(*this->textureManager.getTexture("chars8x8dEncounters", 350));

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
            int xPlayerEnemyDist = abs(this->position.x - this->player.getPosition().x);
            int yPlayerEnemyDist = abs(this->position.y - this->player.getPosition().y);
            int playerEnemyDist = sqrt( (xPlayerEnemyDist)^2 + (yPlayerEnemyDist)^2 );
            return playerEnemyDist;
        }

        void pMove(Direction direction) {};

        void eMove(){
            //Why isn't this working when its being called for ???
            //std::cout << "Ghost is doing something to try to move" << std::endl;
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

            //std::cout << "Ghost is activating the atk function" << std::endl;

            float def = player.stats.defense;
            int dmgRed = def / def + 100; //Damage reduction formula
            float luck = player.stats.luck;

            if( distance() < 3){ //Also add modulo tick eventually ig, add 3x longer modulo for ranged enemies 
                //std::cout << "Ghost is within reach to atk the player and is currently trying to atk them" << std::endl;
                if( (1 + rand() % 30) > luck) { //If player's luck is greater than they dodge the atk, max player luck is 20
                    //std::cout << "Ghost passed luck check and attacking player" << std::endl;
                    int dmg = dmgRed * this->stats.strength;
                    if(dmg < 1){
                        dmg = 1;
                    }
                    this->player.stats.health -= dmg;
                    //std::cout << "This is the player's health " << this->player.stats.health << std::endl;
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