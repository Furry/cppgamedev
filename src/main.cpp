#include <iostream>
#include "SFML/Graphics.hpp"
#include "libs/atlas.h"
#include "modules/perlin.h"

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works even better uwu!");

    Atlas crystalCave("static/textures/crystalCaveObjects8x8.png", 8, 8);

    Perlin perlin(4);
    cout << perlin.getNoise(0, 0) << endl;
    cout << "Size: " << crystalCave.getCount() << endl;
    sf::Texture* textures[] = {
        crystalCave.getTexture(165),
        crystalCave.getTexture(166),
        crystalCave.getTexture(167),
        crystalCave.getTexture(168),
        crystalCave.getTexture(169)
    };

    sf::Texture* texture = crystalCave.getTexture(165);
    sf::Sprite sprite;

    sprite.setTexture(*texture);
    int tally = 0;
    int indx = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // printf("Event: %d", event.type);

        window.clear();

        // Scale the sprite up and draw it in the center

        // Draw the sprite across the screen (its 8by8)

        // Scale the sprite and draw it across the screen
        sprite.setScale(4, 4);
        sprite.setPosition(0, 0);
        window.draw(sprite);

        // Draw a 4x4 grid of the sprites
        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 25; j++) {
                sprite.setPosition(i * 32, j * 32);
                // cout << perlin.getNoise(i, j) << endl;
                sprite.setTexture(*textures[perlin.getNoise(i, j)]);
                window.draw(sprite);
            }
        }

        // Quit the app
        // window.close();


        // window.draw(sprite);

        window.display();
        tally += 1;
    }

    return 0;
}