#include <iostream>
#include <fstream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "libs/atlas.h"
#include "modules/perlin.h"

#include "core/game.cpp"
#include "core/level/level.h"
#include "libs/utils.h"
#include "libs/ticker.h"
#include "libs/layerreader.h"
#include "core/level/crystalcave.cpp"
#include "core/level/dungeon.cpp"
#include "core/level/hell.cpp"
#include "./ui.h"

#include <sstream>

using namespace std;

// https://www.fesliyanstudios.com/royalty-free-music/downloads-c/8-bit-music/6 from here!
bool playBackgroundMusic() {
    static sf::Music backgroundMusic;

    if (!backgroundMusic.openFromFile("static/audio/background_music.wav")) {
        std::cout << "Error loading background music" << std::endl;
        return false;
    }

    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(25);

    backgroundMusic.play();

    return true;
}

int main() {

    int pauseDB = 200;  // Debounce time in milliseconds
    sf::Clock debounceClock;  // Clock for measuring time between key presses

    //This is to control which level is being generated
    int levelControl = 1;

    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works even better uwu!");

    // ! Create game instance
    Game game(0);

    TextureManager m = game.getTextureManager();
    Player player = Player(&m);
    player.setPosition(getPositionInBound(100, 2288, 100, 2252));
    CrystalCave ccLvl = CrystalCave(0, &player);
    Dungeon dungeonLvl = Dungeon(0, &player);
    Hell hellLvl = Hell(0, &player);


    m.load("SakuraEnvironment8x8", 8, 8);
    m.load("crystalCaveObjects8x8", 8, 8);
    m.load("lofiChar", 8, 8);
    m.load("chars8x8dEncounters", 8, 8);
    m.load("parasiteDenObjects8x8", 8, 8);
    m.load("mountainTempleObjects8x8", 8, 8);

    displayWelcomeScreen(&window);

    playBackgroundMusic();
    sf::Sprite sprite;

    player.stats.speed = 6;
    int tally = 0;

    while (window.isOpen()) {
        tally++;
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // The evolution of how player is accessed heh
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            // player.setPosition(sf::Vector2f(player.getPosition().x, player.getPosition().y - 1));
            // player.move(Direction::UP);
            //ccLvl.getPlayer().pMove(Direction::UP);
            player.pMove(Direction::UP);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            player.pMove(Direction::DOWN);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            player.pMove(Direction::LEFT);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            player.pMove(Direction::RIGHT);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            // Get position of mouse relative to window
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            // turn it inito 2f
            sf::Vector2f mousePos2f = sf::Vector2f(mousePos.x, mousePos.y);

            // Get position of mouse relative to player
            sf::Vector2f mousePosPlayer = window.mapPixelToCoords(mousePos, player.getView());
            // lvl.getPlayer().castDefaultSpell(mousePosPlayer, &lvl);

            switch (levelControl) {
                case 1:
                    ccLvl.nova(mousePosPlayer);
                    break;
                case 2:
                    dungeonLvl.nova(mousePosPlayer);
                    break;
                case 3:
                    hellLvl.nova(mousePosPlayer);
                    break;
                default:
                    break;
            }
        }

        if (player.stats.health < 0) {
            displayGameOverScreen(&window);
        }

        // If escape pressed, pause the game
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            sf::Time elapsed = debounceClock.getElapsedTime();

            if (elapsed.asMilliseconds() >= pauseDB) {
                displayPauseGame(&window);
                debounceClock.restart();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            levelControl = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            levelControl = 2;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
            levelControl = 3;
        }

        // Move the view to the player
        window.setView(player.getView());

        window.clear();

        player.update(tally, ccLvl);

    
        // Scale the sprite and draw it across the screen
        sprite.setScale(4, 4);
        sprite.setPosition(0, 0);
        // window.draw(sprite);



        if(levelControl == 1) {    //This is crystal isles level
            bool renderQuestion = false;
            ccLvl.renderMap(sprite, &window, m);
            ccLvl.updateEnemies(tally, m, &window); 
            dungeonLvl.clearEnemies();
            hellLvl.clearEnemies();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) ) {
                renderQuestion = true;
            }

            if(renderQuestion) {
                ccLvl.dungeonKeeper.renderQuestion(&window);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) && player.pts >= 5) {
                levelControl = 2;
            }
        }
        else if(levelControl == 2) {   //This is dungeon level
            bool renderQuestion = false;
            dungeonLvl.renderMap(sprite, &window, m);
            dungeonLvl.updateEnemies(tally, m, &window); 
            ccLvl.clearEnemies();
            hellLvl.clearEnemies();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::T) ) {
                renderQuestion = true;
            }

            if(renderQuestion) {
                ccLvl.dungeonKeeper.renderQuestion(&window);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y) && player.pts >= 10) {
                levelControl = 3;
            }
        }
        else {  //This is hell level
            hellLvl.renderMap(sprite, &window, m);
            hellLvl.updateEnemies(tally, m, &window); 
            ccLvl.clearEnemies();
            dungeonLvl.clearEnemies();
        }


        //Work on stopping player movement's when the npc screen is open 

        //if( player.pts >= 5) {  //This allows for the player to go to the next level
        //    dungeonLvl.renderMap(sprite, &window, m);
        //    //dungeonLvl.updateEnemies(tally, m, &window); 
        //    ccLvl.clearEnemies();
        //    hellLvl.clearEnemies();
        //}
        //if( player.pts >= 10) { //This allows for the player to go to the 3rd level
        //    hellLvl.renderMap(sprite, &window, m);
        //    //hellLvl.updateEnemies(tally, m, &window); 
        //    ccLvl.clearEnemies();
        //    dungeonLvl.clearEnemies();
        //}

        
        player.render(&window);
        player.renderHud(&window);
        window.display();
        //tally += 1;

        // 60 fps
        sf::sleep(sf::milliseconds(16));
    }

    return 0;
}
