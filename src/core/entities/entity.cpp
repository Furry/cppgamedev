#include "entity.h"

#include <iostream>

Entity::Entity () {
    this->position = sf::Vector2f(0, 0);
}

void Entity::update(int tick) {};
void Entity::render(sf::RenderWindow* window) {};
void Entity::setPosition(sf::Vector2f position) {
    this->position = position;
};

sf::Vector2f Entity::getPosition() {
    return this->position;
};