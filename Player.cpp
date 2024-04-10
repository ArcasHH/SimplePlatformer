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


void Player::input() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        moveLeft();
    }
    else
    {
        stopLeft();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        moveRight();
    }
    else
    {
        stopRight();
    }
}
void Player::update(){
    if (rightPressed){
        position.x += speed ;
    }
    if (leftPressed){
        position.x -= speed ;
    }
    sprite.setPosition(position);
}
void  Player::draw(sf::RenderWindow& window) {
    window.draw(getSprite());
}