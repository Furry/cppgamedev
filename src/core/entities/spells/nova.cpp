
#include <SFML/Graphics.hpp>
#include "./spell.h"

class Nova : public Spell {

    private:
        int spellCost = 10;
        int ticksAlive = 0;
        int ticksToLive = 100;
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

    void update(int tick, Level level) {
        this->ticksAlive++;
        if (this->ticksAlive >= this->ticksToLive) {
            // Delete itself inside of level
        } else {
            // Update explosion size and position
            float deltaTime = 1.0f / 60.0f; // assuming 60 fps
            this->scaleFactor += 0.1f * deltaTime;
            this->explosion.setScale(this->scaleFactor, this->scaleFactor);
            this->explosion.setPosition(this->position - sf::Vector2f(this->explosion.getRadius() * this->scaleFactor, this->explosion.getRadius() * this->scaleFactor));
        }
    }
};
