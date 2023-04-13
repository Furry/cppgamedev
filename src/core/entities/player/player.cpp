#include <SFML/Graphics.hpp>

#include "player.h"
#include "../spells/nova.cpp"
#include <iostream>
#include <sstream> 

// add default
Stats createStats() {
    return Stats  {
        8, 8, 100, 100, 1, 25, 1, 1, 1, 1
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

void Player::damage(int amount) {
    this->stats.health -= amount;

    if (this->stats.health <= 0) {
        this->stats.health = 0;
    }

    std::cout << "Player Killed!" << std::endl;
}

void Player::attack(){
    int x = 5;
}

void Player::renderHud(sf::RenderWindow* window) {
    int currentHealth = this->stats.health;
    int maxHealth = this->stats.maxHealth;

    int currentMana = this->stats.mana;
    int maxMana = this->stats.maxMana;
    int xpos = this->position.x;
    int ypos = this->position.y;

    float healthPercent = static_cast<float>(currentHealth) / maxHealth;
    float manaPercent = static_cast<float>(currentMana) / maxMana;

    sf::Vector2f healthBarSize(75, 6);
    sf::Vector2f manaBarSize(75, 6);

    sf::RectangleShape healthBarOuter(healthBarSize + sf::Vector2f(2, 2));
    healthBarOuter.setFillColor(sf::Color::Transparent);
    healthBarOuter.setOutlineColor(sf::Color::Black);
    healthBarOuter.setOutlineThickness(1);
    healthBarOuter.setPosition(xpos - healthBarSize.x / 2, ypos + 55);

    sf::RectangleShape healthBar(healthBarSize);
    healthBar.setFillColor(sf::Color::Red);
    healthBar.setSize(sf::Vector2f(healthBarSize.x * healthPercent, healthBarSize.y));
    healthBar.setPosition(xpos - healthBarSize.x / 2 + 1, ypos + 55 + 1);

    sf::RectangleShape manaBarOuter(manaBarSize + sf::Vector2f(2, 2));
    manaBarOuter.setFillColor(sf::Color::Transparent);
    manaBarOuter.setOutlineColor(sf::Color::Black);
    manaBarOuter.setOutlineThickness(1);
    manaBarOuter.setPosition(xpos - manaBarSize.x / 2, ypos + healthBarSize.y + 60);

    sf::RectangleShape manaBar(manaBarSize);
    manaBar.setFillColor(sf::Color::Blue);
    manaBar.setSize(sf::Vector2f(manaBarSize.x * manaPercent, manaBarSize.y));
    manaBar.setPosition(xpos - manaBarSize.x / 2 + 1, ypos + healthBarSize.y + 61);


    // sf::Font font;
    // if (!font.loadFromFile("path/to/font.ttf")) {
    //     // Handle font loading error
    // }

    sf::Text healthText;
    // healthText.setFont(font);
    healthText.setString(std::to_string(static_cast<int>(healthPercent * 100)) + "%");
    healthText.setCharacterSize(10);
    healthText.setFillColor(sf::Color::White);
    healthText.setPosition(xpos - healthText.getLocalBounds().width / 2, ypos + 50 + 2);

    window->draw(healthBarOuter);
    window->draw(healthBar);
    window->draw(manaBarOuter);
    window->draw(manaBar);
    window->draw(healthText);

    //Draw's pt board
    sf::RectangleShape board;
    board.setSize( sf::Vector2f(75, 50) );
    board.setFillColor( sf::Color::Black);
    board.setPosition( this->position.x + 330, this->position.y - 400);
    window->draw(board);

    //Draw's pts on the pt board
    sf::Font font;
    sf::Text textTest;
    font.loadFromFile("fonts/arial.ttf");
    textTest.setFont(font);
    textTest.setPosition(this->position.x + 335, this->position.y - 390);
    std::stringstream ss; //#include <sstream>  https://en.sfml-dev.org/forums/index.php?topic=8368.0
    ss << this->pts;
    textTest.setString( ss.str() );
    textTest.setCharacterSize(24);
    textTest.setFillColor(sf::Color::White);
    //textTest.setStyle(sf::Text::Bold | sf::Text::Underlined);
    textTest.setStyle(sf::Text::Bold);
    window->draw( textTest );
}