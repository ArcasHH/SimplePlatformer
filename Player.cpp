#include "Player.h"

Player::Player(){
    speed = 400;

    texture.loadFromFile("images/hero.jpg");
    sprite.setTexture(texture);

    position.x = 300;
    position.y = 300;
    leftPressed = false; 
    rightPressed = false;
}

sf::Sprite Player::getSprite(){
    return sprite;
}

void Player::moveLeft(){
    leftPressed = true;
}

void Player::moveRight(){
    rightPressed = true;
}

void Player::stopLeft(){
   leftPressed = false;
}

void Player::stopRight(){
    rightPressed = false;
}

void Player::update(float elapsedTime){
    if (rightPressed){
        position.x += speed * elapsedTime;
    }
    if (leftPressed){
        position.x -= speed * elapsedTime;
    }
    sprite.setPosition(position);
}