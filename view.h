#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
using namespace sf;

sf::View view;

void getplayercoordinateforview(float x, float y) {
	float tempX = x; float tempY = y;

	//if (x < 320) tempX = 320;
	//if (y < 240) tempY = 240;
	//if (y > 554) tempY = 554;

	view.setCenter(tempX, tempY); 

}

void viewmap(float time) { //функция для перемещения камеры по карте. принимает время sfml
	if (Keyboard::isKeyPressed(Keyboard::D)) {
		view.move(PLAYER_SPEED * time, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::S)) {
		view.move(0, PLAYER_SPEED * time);
	}
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		view.move(-PLAYER_SPEED * time, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::W)) {
		view.move(0, -PLAYER_SPEED * time);
	}
}
