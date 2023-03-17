#include <SFML/Graphics.hpp>

#include "player.h"
#include <iostream>

Player::Player(TextureManager textureManager) {
    this->textureManager = textureManager;
    this->sprite = sf::Sprite();
    // access the real value not the pointer
    // sf::Texture texture = textureManager->getTexture("lofiChar", 15)
    // this->sprite.setTexture();
}

Player::~Player() {
    // Clean up uwu
    // delete textures;
}

void Player::update(int tick) {
    // if (tick == 0) {
    //     this->sprite.setTexture(*this->textureManager.getTexture("lofiChar", 15));
    //     this->sprite.setScale(6, 6);
    //     this->setPosition(sf::Vector2f(400, 400));
    // }

    std::cout << "tick " << tick << std::endl;
    if (tick % 20 == 0) {
        std::cout << "tick 20" << std::endl;
        // Set their texture to 31
        // this->sprite.setTexture(*this->textureManager.getTexture("lofiChar", 31));
    } else if (tick % 10 == 0) {
        std::cout << "tick 10" << std::endl;
        // Set their texture to 15
        this->sprite.setTexture(*this->textureManager.getTexture("lofiChar", 15));
    }
}

void Player::setPosition(sf::Vector2f position) {
    this->position = position;
    this->sprite.setPosition(position);
}

void Player::render(sf::RenderWindow* window) {
    // Draw it at it's position
    this->sprite.setPosition(this->position);
    window->draw(this->sprite);
}
