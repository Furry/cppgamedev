#include <iostream>
#include "SFML/Graphics.hpp"
#include "libs/atlas.h"
#include "modules/perlin.h"

#include "core/game.cpp"
#include "libs/ticker.h"

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works even better uwu!");

    // ! Critical: Create game instance
    Game game(0);

    TextureManager m = game.getTextureManager();
    m.load("crystalCaveObjects8x8", 8, 8);
    m.load("lofiChar", 8, 8);

    game.start();

    // Player player(charTextures);

    Perlin perlin(4);
    // cout << perlin.getNoise(0, 0) << endl;
    // cout << "Size: " << crystalCave.getCount() << endl;
    sf::Texture* textures[] = {
        m.getTexture("crystalCaveObjects8x8", 165),
        m.getTexture("crystalCaveObjects8x8", 166),
        m.getTexture("crystalCaveObjects8x8", 167),
        m.getTexture("crystalCaveObjects8x8", 168),
        m.getTexture("crystalCaveObjects8x8", 169)
    };

    sf::Sprite sprite;
    sprite.setTexture(*textures[0]);
    // int tally = 0;
    // int indx = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // printf("Event: %d", event.type);

        window.clear();


        // Scale the sprite and draw it across the screen
        sprite.setScale(4, 4);
        sprite.setPosition(0, 0);
        window.draw(sprite);

        // Draw a 4x4 grid of the sprites
        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 25; j++) {
                sprite.setPosition(i * 32, j * 32);
                sprite.setTexture(*textures[perlin.getNoise(i, j)]);
                window.draw(sprite);
            }
        }

        // game.player->render(&window);
    //     // Quit the app
    //     // window.close();


    //     // window.draw(sprite);

        window.display();
    //     tally += 1;
    }

    return 0;
}