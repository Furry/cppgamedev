#include <iostream>
#include "SFML/Graphics.hpp"
#include "libs/atlas.h"
#include "modules/perlin.h"

#include "core/game.cpp"
#include "core/level/level.h"
#include "libs/ticker.h"

#include "core/level/crystalcave.cpp"
//#include "core/entities/enemy/ghost.cpp"

#include <sstream>

using namespace std;

int main() {

    //This is just to test if I can display integers and strings
    int testPrintIntBoard = 4;

    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works even better uwu!");

    // ! Create game instance
    Game game(0);

    // Level lvl = Level("crystalCaveObjects8x8", {165, 166, 167, 168, 169}, sf::Vector2f(400, 400), 0);
    // Create inline vector of ints
    // std::vector<int> atlasIndices = (std::vector<int>) {165, 166, 167, 168, 169};
    TextureManager m = game.getTextureManager();
    Player player = Player(&m);
    CrystalCave lvl = CrystalCave(0, &player);

    m.load("crystalCaveObjects8x8", 8, 8);
    m.load("lofiChar", 8, 8);
    m.load("chars8x8dEncounters", 8, 8);

    //Ghost g = Ghost(&m);
    //lvl.addEnemies(&g);
    // game.start();
    lvl.start();


    // Check if player and  lvl.getPlayer() are the same
    std::cout << &player << std::endl;
    Player p2 = lvl.getPlayer();

    // Player player(charTextures);

    Perlin perlin(4);
    sf::Texture* textures[] = {
        m.getTexture("crystalCaveObjects8x8", 165),
        m.getTexture("crystalCaveObjects8x8", 166),
        m.getTexture("crystalCaveObjects8x8", 167),
        m.getTexture("crystalCaveObjects8x8", 168),
        m.getTexture("crystalCaveObjects8x8", 169)
    };

    sf::Sprite sprite;
    sprite.setTexture(*textures[0]);

    player.stats.speed = 6;
    int tally = 0;
    // int indx = 0;
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
            lvl.getPlayer().pMove(Direction::UP);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            // player.setPosition(sf::Vector2f(player.getPosition().x, player.getPosition().y + 1));
            // player.move(Direction::DOWN);
            lvl.getPlayer().pMove(Direction::DOWN);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            // player.setPosition(sf::Vector2f(player.getPosition().x - 1, player.getPosition().y));
            // player.move(Direction::LEFT);
            lvl.getPlayer().pMove(Direction::LEFT);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            // player.setPosition(sf::Vector2f(player.getPosition().x + 1, player.getPosition().y));
            // player.move(Direction::RIGHT);
            lvl.getPlayer().pMove(Direction::RIGHT);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            // Get position of mouse relative to window
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            // Get position of mouse relative to player
            sf::Vector2f mousePosPlayer = window.mapPixelToCoords(mousePos, player.getView());
            // lvl.getPlayer().castDefaultSpell(mousePosPlayer, &lvl);
            lvl.nova(mousePosPlayer);
        }

        // printf("Event: %d", event.type);

        // Move the view to the player
        window.setView(player.getView());

        window.clear();
        player.update(tally, lvl);


        // Scale the sprite and draw it across the screen
        sprite.setScale(4, 4);
        sprite.setPosition(0, 0);
        // window.draw(sprite);

        // Draw a 4x4 grid of the sprites
        for (int i = -100; i < 100; i++) {
            for (int j = -100; j < 100; j++) {
                sprite.setPosition(i * 32, j * 32);
                sprite.setTexture(*textures[perlin.getNoise(i, j)]);
                window.draw(sprite);
            }
        }

        /** pt board
        sf::RectangleShape board;
        board.setSize( sf::Vector2f(200, 150) );
        board.setFillColor( sf::Color::Black);
        board.setPosition( lvl.getPlayer().getPosition().x + 300, lvl.getPlayer().getPosition().y - 400);
        window.draw(board);*/


        sf::Text textTest;
        std::stringstream ss; //#include <sstream>  https://en.sfml-dev.org/forums/index.php?topic=8368.0
        ss << testPrintIntBoard;

        textTest.setString( ss.str().c_str() );

        window.draw( textTest );

        lvl.updateEnemies(tally, m, &window);  //Something being added here
        //lvl.enemyAI();
        player.render(&window);
        player.renderHud(&window);
        window.display();
        //tally += 1;
    }

    return 0;
}