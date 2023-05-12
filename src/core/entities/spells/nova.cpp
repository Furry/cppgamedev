#include "nova.h"
#include <iostream>
#include <cmath>
#include <algorithm>

Nova::Nova(sf::Vector2f position) {
    this->spellCost = 10;
    this->ticksAlive = 0;
    this->ticksToLive = 25;
    this->position = position;
    this->explosion.setRadius(30);
    this->explosion.setPosition(position);
    this->explosion.setFillColor(sf::Color::Yellow);
    this->scaleFactor = 1.0f;
}

Nova::~Nova() {}

void Nova::render(sf::RenderWindow* window) {
    window->draw(this->explosion);
}

bool Nova::isDead() {
    return this->ticksAlive >= this->ticksToLive;
}

void Nova::update(int tick, Level &level) {
    this->ticksAlive++;

    if (this->ticksAlive >= this->ticksToLive) {
        return;
    } else {
        float deltaTime = 1.0f / 45.0f;
        this->scaleFactor += 0.1f * deltaTime;
        this->explosion.setScale(this->scaleFactor, this->scaleFactor);
        this->explosion.setRadius(10 * this->scaleFactor);
        this->explosion.setPosition(this->position - sf::Vector2f(this->explosion.getRadius(), this->explosion.getRadius()));
    }
}

bool Nova::doesCollide(sf::Vector2f position) {
    sf::Vector2f explosionPosition = this->position;
    float explosionRadius = this->explosion.getRadius();

    float dx = explosionPosition.x - position.x;
    float dy = explosionPosition.y - position.y;
    float distanceSquared = dx * dx + dy * dy;

    return distanceSquared <= (explosionRadius * explosionRadius);
}
