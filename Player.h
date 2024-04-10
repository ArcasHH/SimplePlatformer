#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"

class Player{
private:
	sf::Vector2f position;
	sf::Sprite sprite;
	sf::Texture texture;

	bool leftPressed;
	bool rightPressed;

	float speed;

public:
	Player();
	sf::Sprite getSprite();
	void moveLeft();
	void moveRight();
	void stopLeft();
	void stopRight();
	
	void input();
	void update();
	void draw(sf::RenderWindow& window);
};
