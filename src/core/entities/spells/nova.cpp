#include <SFML/Graphics.hpp>
#include "./spell.h"
#include "../../level/level.h"
#include <iostream>
#include <cmath>
#include <algorithm>>

class Nova : public Spell {

    private:
        int spellCost = 10;
        int ticksAlive = 0;
        int ticksToLive = 25;
        sf::Vector2f position;
        sf::CircleShape explosion;
        float scaleFactor = 1.0f;
    public:
        Nova(sf::Vector2f position) {
            this->position = position;
            this->explosion.setRadius(10);
            this->explosion.setPosition(position);
            this->explosion.setFillColor(sf::Color::Yellow);
        }

    ~Nova() {}

    void render(sf::RenderWindow* window) {
        window->draw(this->explosion);
    }

    bool isDead() {
        return this->ticksAlive >= this->ticksToLive;
    }

    void update(int tick, Level &level) {
        this->ticksAlive++;

        // Convert level to CrystalCave
        // level.damageInRadius(this->position, 10 * this->scaleFactor, 10);

        if (this->ticksAlive >= this->ticksToLive) {
            // Delete itself inside of level
            // this->~Nova(); // Call the destructor explicitly
            return; // Ensure we don't execute further after destruction
        } else {
            // Update explosion size and position
            float deltaTime = 1.0f / 45.0f; // assuming 45 fps
            this->scaleFactor += 0.1f * deltaTime;
            this->explosion.setScale(this->scaleFactor, this->scaleFactor);
            this->explosion.setRadius(10 * this->scaleFactor); // Update the radius based on the scaleFactor
            this->explosion.setPosition(this->position - sf::Vector2f(this->explosion.getRadius(), this->explosion.getRadius()));
        }
    }

    bool doesCollide(sf::Vector2f position) {
        sf::Vector2f explosionPosition = this->position;
        float explosionRadius = this->explosion.getRadius();

        // Calculate the distance between the given position and the explosion's center
        float dx = explosionPosition.x - position.x;
        float dy = explosionPosition.y - position.y;
        float distanceSquared = dx * dx + dy * dy;

        // Check if the distance is less than or equal to the explosion radius
        return distanceSquared <= (explosionRadius * explosionRadius);
    }

};
