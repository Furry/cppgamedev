#include <iostream>
#include <fstream>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "libs/atlas.h"
#include "modules/perlin.h"

#include "core/game.cpp"
#include "core/level/level.h"
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

    //This is to control which level is being generated
    int levelControl = 1;

    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works even better uwu!");

    // ! Create game instance
    Game game(0);

    // Level lvl = Level("crystalCaveObjects8x8", {165, 166, 167, 168, 169}, sf::Vector2f(400, 400), 0);
    // Create inline vector of ints
    // std::vector<int> atlasIndices = (std::vector<int>) {165, 166, 167, 168, 169};
    TextureManager m = game.getTextureManager();
    Player player = Player(&m);
    CrystalCave ccLvl = CrystalCave(0, &player);
    Dungeon dungeonLvl = Dungeon(0, &player);
    Hell hellLvl = Hell(0, &player);


    m.load("SakuraEnvironment8x8", 8, 8);
    m.load("crystalCaveObjects8x8", 8, 8);
    m.load("lofiChar", 8, 8);
    m.load("chars8x8dEncounters", 8, 8);
    m.load("parasiteDenObjects8x8", 8, 8);
    m.load("mountainTempleObjects8x8", 8, 8);

    playBackgroundMusic();
    //ccLvl.start();    //Is this even needed anymore ?

    sf::Sprite sprite;
    //sprite.setTexture(*m.getTexture("crystalCaveObjects8x8", 165));   //This one isn't even needed

    player.stats.speed = 6;
    int tally = 0;
    // int indx = 0;
    while (window.isOpen()) {
        // print tally
        // std::cout << "Tally: " << tally << std::endl;
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
            // player.setPosition(sf::Vector2f(player.getPosition().x, player.getPosition().y + 1));
            // player.move(Direction::DOWN);
            //ccLvl.getPlayer().pMove(Direction::DOWN);
            player.pMove(Direction::DOWN);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            // player.setPosition(sf::Vector2f(player.getPosition().x - 1, player.getPosition().y));
            // player.move(Direction::LEFT);
            //ccLvl.getPlayer().pMove(Direction::LEFT);
            player.pMove(Direction::LEFT);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            // player.setPosition(sf::Vector2f(player.getPosition().x + 1, player.getPosition().y));
            // player.move(Direction::RIGHT);
            //ccLvl.getPlayer().pMove(Direction::RIGHT);
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
            ccLvl.nova(mousePosPlayer);
        }
        std::cout << "Player health: " << player.stats.health << std::endl;
        if (player.stats.health < 0) {
            displayGameOverScreen(&window);
        }
        // If escape pressed, pause the game
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            displayPauseGame(&window);
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
            ccLvl.renderMap(sprite, &window, m);
            ccLvl.updateEnemies(tally, m, &window); 
            dungeonLvl.clearEnemies();
            hellLvl.clearEnemies();
        }
        else if(levelControl == 2) {   //This is dungeon level
            dungeonLvl.renderMap(sprite, &window, m);
            //dungeonLvl.updateEnemies(tally, m, &window); 
            ccLvl.clearEnemies();
            hellLvl.clearEnemies();
        }
        else {  //This is hell level
            hellLvl.renderMap(sprite, &window, m);
            //hellLvl.updateEnemies(tally, m, &window); 
            ccLvl.clearEnemies();
            dungeonLvl.clearEnemies();
        }

        
        player.render(&window);
        player.renderHud(&window);
        window.display();
        //tally += 1;

        // 60 fps
        sf::sleep(sf::milliseconds(16));
    }

    return 0;
}
