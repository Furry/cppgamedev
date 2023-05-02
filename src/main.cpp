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
//#include "core/entities/enemy/ghost.cpp"

#include <sstream>

using namespace std;

void pauseGame(sf::RenderWindow *window) {
    // Reset the view to the default view
    sf::View defaultView = window->getDefaultView();
    window->setView(defaultView);
    window->clear();


    sf::RectangleShape background(sf::Vector2f(window->getSize().x, window->getSize().y));
    background.setFillColor(sf::Color(0, 0, 0, 255));
    window->draw(background);

    // Set up the "Game Over" text
    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf")) {
        std::cout << "Error loading font" << std::endl;
    }

    sf::Text pauseText;
    pauseText.setFont(font);
    pauseText.setString("Paused");
    pauseText.setCharacterSize(64);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setStyle(sf::Text::Bold);

    // Center the "Game Over" text on the window
    sf::FloatRect textRect = pauseText.getLocalBounds();
    pauseText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    pauseText.setPosition(sf::Vector2f(window->getSize().x / 2.0f, window->getSize().y / 3.0f));

    window->draw(pauseText);
    window->display();

    sf::Event event;
    while (window->waitEvent(event)) {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) {
            window->close();
            break;
        }
        // If escape key down, break out of the loop
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            return;
        }
    }
}


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

    // Load the png from /static/levels/spirit/layer1.png and read it pixel by pixel
    sf::Image image;
    image.loadFromFile("static/levels/spirit/layer1.png");
    sf::Vector2u size = image.getSize();
    sf::Color color;

    LayerReader layerReader = LayerReader("static/levels/spirit/layer1.txt");

    m.load("SakuraEnvironment8x8", 8, 8);
    m.load("crystalCaveObjects8x8", 8, 8);
    m.load("lofiChar", 8, 8);
    m.load("chars8x8dEncounters", 8, 8);
    m.load("parasiteDenObjects8x8", 8, 8);

    // playBackgroundMusic();
    lvl.start();

    sf::Sprite sprite;
    sprite.setTexture(*m.getTexture("crystalCaveObjects8x8", 165));

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
            // turn it inito 2f
            sf::Vector2f mousePos2f = sf::Vector2f(mousePos.x, mousePos.y);

            // Get position of mouse relative to player
            sf::Vector2f mousePosPlayer = window.mapPixelToCoords(mousePos, player.getView());
            // lvl.getPlayer().castDefaultSpell(mousePosPlayer, &lvl);
            lvl.nova(mousePosPlayer);
        }
        // If escape pressed, pause the game
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            pauseGame(&window);
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

        // Loop through each pixel in the image
        for (int i = 0; i < size.x; i++) {
            for (int j = 0; j < size.y; j++) {
                // Print the RGB
                color = image.getPixel(i, j);
                int index = layerReader.getTile(color.r, color.g, color.b, color.a);
                if (index != -1) {
                    sprite.setPosition(i * 32, j * 32);
                    sprite.setTexture(
                        *m.getTexture("parasiteDenObjects8x8", layerReader.getTile(color.r, color.g, color.b, color.a)));
                    window.draw(sprite);
                }
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

        // 60 fps
        sf::sleep(sf::milliseconds(16));
    }

    return 0;
}
