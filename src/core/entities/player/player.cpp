#include <SFML/Graphics.hpp>

#include "player.h"
#include <iostream>

// add default
Stats createStats() {
    return Stats  {
        20, 20, 100, 100, 1, 1, 1, 1, 1, 1
    };
}

Player::Player(TextureManager *textureManager) {
    this->textureManager = *textureManager;
    this->sprite = sf::Sprite();
    this->sprite.setScale(6, 6);
    this->stats = createStats();
    // Create a new view for the player
    this->view = sf::View(sf::Vector2f(400, 400), sf::Vector2f(800, 800));
    // Print out the sprite manager

    // this->sprite.setTexture(*this->textureManager.getTexture("lofiChar", 15));
    // access the real value not the pointer
    // sf::Texture initial = *this->textureManager.getTexture("lofiChar", 15);
    // this->sprite.setTexture(textureManager.getTexture("lofiChar", 15));
}

void Player::update(int tick, Level level) {
    if (tick == 1) {
        std::cout << "Setting texture to 15" << std::endl;
        this->sprite.setTexture(*this->textureManager.getTexture("lofiChar", 15));
    }

    if (tick % 200 == 0) {
        // Set their texture to 31
        this->sprite.setTexture(*this->textureManager.getTexture("lofiChar", 31));
    } else if (tick % 100 == 0) {
        // Set their texture to 15
        this->sprite.setTexture(*this->textureManager.getTexture("lofiChar", 15));
    }
}

void Player::setPosition(sf::Vector2f position) {
    this->position = position;
    this->sprite.setPosition(position);
    this->view.setCenter(position);
}

void Player::render(sf::RenderWindow* window) {
    // Draw it at it's position
    this->sprite.setPosition(this->position);
    this->view.setCenter(this->position);
    window->draw(this->sprite);
}

sf::View Player::getView() {
    return this->view;
}

sf::Vector2f Player::getPosition() {
    return this->position;
}

void Player::eMove() {
    int x = 4;
}

void Player::pMove(Direction direction){
    switch (direction) {
        case UP:
            this->position.y -= this->stats.speed;
            // Face the sprite to the left
            // Flip the sprite's texture horizontally
            this->sprite.setOrigin(sprite.getLocalBounds().width / 2, 0);
            this->sprite.setScale(-6, 6);
            break;
        case DOWN:
            this->position.y += this->stats.speed;
            // Face the sprite to the right
            this->sprite.setOrigin(sprite.getLocalBounds().width / 2, 0);
            this->sprite.setScale(6, 6);
            break;
        case LEFT:
            this->position.x -= this->stats.speed;
            // Face the sprite to the left
            this->sprite.setOrigin(sprite.getLocalBounds().width / 2, 0);
            this->sprite.setScale(-6, 6);
            break;
        case RIGHT:
            this->position.x += this->stats.speed;
            // Face the sprite to the right
            this->sprite.setOrigin(sprite.getLocalBounds().width / 2, 0);
            this->sprite.setScale(6, 6);
            break;
    }
}

void Player::attack(){
    int x = 5;
}

void Player::renderHud(sf::RenderWindow* window) {
    // Draw the player's health
    sf::RectangleShape healthBar;
    sf::RectangleShape manaBar;

    healthBar.setSize(sf::Vector2f(100, 10));
    healthBar.setFillColor(sf::Color::Red);
    healthBar.setPosition(this->position.x - 50, this->position.y - 50);

    manaBar.setSize(sf::Vector2f(100, 10));
    manaBar.setFillColor(sf::Color::Blue);
    manaBar.setPosition(this->position.x - 50, this->position.y - 38);

    window->draw(healthBar);
    window->draw(manaBar);

    //Draw's pt board
    sf::RectangleShape board;
    board.setSize( sf::Vector2f(200, 150) );
    board.setFillColor( sf::Color::Black);
    board.setPosition( this->position.x + 290, this->position.y - 400);
    window->draw(board);
}