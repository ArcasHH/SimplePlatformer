#include "Object.h"

Object::Object(std::string file, int x, int y) {
	pos.x = x;
	pos.y = y;
	texture.loadFromFile(file);
	sprite.setTexture(texture);
	sprite.setPosition(pos.x, pos.y);
}

void Object::draw(sf::RenderWindow& window) {
	window.draw(getSprite());
}
sf::Sprite Object::getSprite() {
	return sprite;
}

PushButton::PushButton(std::string file, int x, int y, sf::IntRect area, sf::Color b_color, sf::Color c_color) {
	
	pos.x = x;
	pos.y = y;

	texture.loadFromFile(file);
	size.x = texture.getSize().x;
	size.y = texture.getSize().y;

	rect = sf::IntRect(pos.x, pos.y, size.x, size.y);

	sprite.setTexture(texture, &rect);
	sprite.setPosition(pos.x, pos.y);
	
	base_color = b_color;
	clicked_color = c_color;
	is_pointed = false;
	is_clicked = false;
	
}
void PushButton::draw(sf::RenderWindow& window) {
	window.draw(getSprite());
}
void PushButton::update(sf::RenderWindow& window) {
	if (is_pos(window) || is_clicked) {
		sprite.setColor(clicked_color);
	}
	else if (!is_clicked)
		sprite.setColor(base_color);
}
bool  PushButton::is_pos(sf::RenderWindow& window) {
	if (rect.contains(sf::Mouse::getPosition(window))) {
		return true;
	}
	return false;
}
sf::Sprite PushButton::getSprite() {
	return sprite;
}