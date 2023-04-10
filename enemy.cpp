

#include <SFML/Graphics.hpp>

#include "enemy.h"
#include <iostream>
#include <cmath>

//Default stats


Stats createStats(){
    return Stats {
        20, 20, 100, 100, 1, 1, 1, 1, 1, 1
    };
}


Enemy::Enemy() {
    this->sprite = sf::Sprite();
    this->sprite.setScale(5, 5);
    this->stats = createStats();
}


void Enemy::update(int tick, Level level){
    this->player = level.getPlayer();
}

void Enemy::setPosition(sf::Vector2f position){
    this->position = position;
    this->sprite.setPosition(position);
}

void Enemy::render(sf::RenderWindow* window){
    this->sprite.setPosition(this->position);
    window->draw(this->sprite);
}

int Enemy::distance(){
    sf::Vector2f test = this->position;
    int playerEnemyDist = sqrt( (this->position.x - this->player.getPosition().x)^2 + (this->position.y - this->player.getPosition().y)^2 );
    return playerEnemyDist;
}

//TO-DO
void Enemy::move(){
    
    //Enemy x coordinate movement in accordinate to player x pos
    if( this->position.x < player.getPosition().x ) {
        this->position.x += this->stats.speed;

    }
    else if( this->position.x > player.getPosition().x ) {
        this->position.x -= this->stats.speed;
    }//Should be an else here but it'll do nothing as the playere & enemy x coordinates match and no movement needs to be done
    

    //Enemy y coordinate movement in accordance to player y pos
    if( this->position.y < player.getPosition().y ) {
        this->position.y += this->stats.speed;

    }
    else if( this->position.y > player.getPosition().y ) {
        this->position.y -= this->stats.speed;
    }//Should be an else here but it'll do nothing as the playere & enemy y coordinates match and no movement needs to be done
    
}


void Enemy::attack(){

    float def = player.getStats().defense;
    int dmgRed = def / def + 100; //Damage reduction formula
    float luck = player.getStats().luck;

    if( distance() < 3){
        if( (1 + rand() % 20) < luck) { //If player's luck is greater than they dodge the atk
            int dmg = dmgRed * this->stats.strength;
            player.getStats().health -= dmg;
        }
    }
    
}

sf::Sprite Enemy::getSprite(){
    return this->sprite;
}

sf::Vector2f Enemy::getPosition(){
    return this->position;
}


