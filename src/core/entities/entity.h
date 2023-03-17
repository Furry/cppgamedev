#include <SFML/Graphics.hpp>

#ifndef ENTITY_H
class Entity {
    sf::Vector2f position;

    public:
        Entity();
        void update(int tick);
        void render(sf::RenderWindow* window);

        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition();
};
#endif