

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <sstream> 


#include "../entity.h"
#include "../player/player.h"
#include "../../level/level.h"


class DungeonKeeper : public Entity {
    private:
        sf::Sprite sprite;
        TextureManager textureManager;
        sf::Vector2f position, playerPos;
        int renderInt;
        int pt = 0;

    public:
        //Sprite 322
        DungeonKeeper(TextureManager *textureManager) {
            this->textureManager = *textureManager;
            this->sprite = sf::Sprite();
            this->sprite.setScale(5,5);
            this->sprite.setTexture(*this->textureManager.getTexture("chars8x8dEncounters", 322) );
            renderInt = 1;
        }

        ~DungeonKeeper() {

        }


        void update(int tick, Level level) {

        }

        void updatePlayer(sf::Vector2f playerPos, int pt) {
            this->playerPos = playerPos;
            this->pt = pt;
        }

        void render(sf::RenderWindow* window) {

            this->sprite.setPosition(this->position);
            window->draw(this->sprite);

            if(renderInt == 1) {
                renderPopup(window);
            }
            else if(renderInt == 2) {
                renderQuestion(window);
            }
            
        }

        void renderQuestion(sf::RenderWindow* window) {

            this->renderInt = 2;
            sf::RectangleShape board;
            sf::Font font;
            sf::Text textTest;
            font.loadFromFile("fonts/arial.ttf");
            textTest.setFont(font);
            std::stringstream ss; 


            if(distance() < 40) {
                if(pt >= 5) {
                    board.setSize( sf::Vector2f(270, 80) );
                    board.setFillColor( sf::Color::Black );
                    board.setPosition( this->position.x - 110, this->position.y - 110 );

                    ss << "You currently have enough points\n to continue to the next level\n Press Y to continue";
                    textTest.setString( ss.str() );
                    textTest.setCharacterSize(16);
                    textTest.setFillColor(sf::Color::White);
                    textTest.setStyle(sf::Text::Bold);
                    textTest.setPosition( this->position.x - 110, this->position.y - 100 );

                    window->draw( board );
                    window->draw( textTest );
                }

                else {

                    board.setSize( sf::Vector2f(270, 80) );
                    board.setFillColor( sf::Color::Black );
                    board.setPosition( this->position.x - 110, this->position.y - 110 );

                    ss << "Hello there young adventurer!\n If you seek the next level\n you first must collect 5 points";
                    textTest.setString( ss.str() );
                    textTest.setCharacterSize(16);
                    textTest.setFillColor(sf::Color::White);
                    textTest.setStyle(sf::Text::Bold);
                    textTest.setPosition( this->position.x - 110, this->position.y - 100 );

                    window->draw( board );
                    window->draw( textTest );
                }
            }
        }

        void renderPopup(sf::RenderWindow* window) {

            if(distance() < 40) {
                sf::RectangleShape board;
                board.setSize( sf::Vector2f(270, 50) );
                board.setFillColor( sf::Color::Black );
                board.setPosition( this->position.x - 110, this->position.y - 60 );

                sf::Font font;
                sf::Text textTest;
                font.loadFromFile("fonts/arial.ttf");
                textTest.setFont(font);
                std::stringstream ss; 
                ss << "Hold t to talk to the gatekeeper";
                textTest.setString( ss.str() );
                textTest.setCharacterSize(16);
                textTest.setFillColor(sf::Color::White);
                textTest.setStyle(sf::Text::Bold);
                textTest.setPosition( this->position.x - 110, this->position.y - 50 );

                window->draw( board );
                window->draw( textTest );
            }
            
        }

        float distance() {

            float deltaX = playerPos.x - position.x;
            float deltaY = playerPos.y - position.y;

            return std::sqrt( (deltaX * deltaX) + (deltaY * deltaY) );
        }

        void setPosition(sf::Vector2f position) {
            //Setting the position of the sprite when its drawn.
            this->position = position;
            this->sprite.setPosition(position);
        }

        void pMove(Direction direction) {};
        void eMove() {};
        void attack() {};
        sf::Vector2f getPosition() {
            return this->position;
        }

};