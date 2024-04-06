#include "Object.h"

Object::Object(std::string file, int x, int y) {
	texture.loadFromFile(file);
	sprite.setTexture(texture);
	pos.x = x;
	pos.y = y;
}

void Object::draw(sf::RenderWindow& window) {
	window.draw(sprite);
}