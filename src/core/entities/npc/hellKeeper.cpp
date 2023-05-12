

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#include "../entity.h"
#include "../player/player.h"
#include "../../level/level.h"


class HellKeeper : public Entity {
    private:
        sf::Sprite sprite;
        TextureManager textureManager;
        sf::Vector2f position;

    public:
        //Sprite 345
        HellKeeper(TextureManager *textureManager) {
            this->textureManager = *textureManager;
            this->sprite = sf::Sprite();
            this->sprite.setScale(5,5);
            this->sprite.setTexture(*this->textureManager.getTexture("chars8x8dEncounters", 345));
        }


        void update(int tick, Level level) {

        }

        void render(sf::RenderWindow* window) {
            this->sprite.setPosition(this->position);
            window->draw(this->sprite);
        }

        void renderQuestion(sf::RenderWindow* window, int pt) {
            
            if(pt >= 10) {  //Player has enough pts

                if( response() ) {  //They agree to go to next lvl

                }
                else {  //They don't go to the next lvl just yet

                }
            }   
            
            else {  //The player doesn't have enough pts

            }
        }

        bool response() {

        }
        

        void setPosition(sf::Vector2f position) {
            //Setting the position of the sprite when its drawn.
            this->position = position;
            this->sprite.setPosition(position);
        }




        //void pMove(Direction direction);
        //void eMove();
        //void attack();
        //sf::Vector2f getPosition();






};