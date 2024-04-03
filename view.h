#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

sf::View view;

void getplayercoordinateforview(float x, float y) {
	float tempX = x; float tempY = y;
	view.setCenter(tempX, tempY); 
}

void viewmap(float time) { //функция для перемещения камеры по карте. принимает время sfml
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		view.move(PLAYER_SPEED * time, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		view.move(0, PLAYER_SPEED * time);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		view.move(-PLAYER_SPEED * time, 0);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		view.move(0, -PLAYER_SPEED * time);
	}
}
