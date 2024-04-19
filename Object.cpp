#include "Object.h"

// Object methods///////////////////////////////////////////////////////////////////////////////////
Object::Object(std::string file, float x, float y) {
	texture.loadFromFile(file);
	sprite.setTexture(texture);
	rect.left = x;
	rect.top = y;
	rect.width = sprite.getTextureRect().width;
	rect.height = sprite.getTextureRect().height;
	sprite.setPosition(rect.left, rect.top);
}
void Object::draw(sf::RenderWindow& window) {
	window.draw(getSprite());
}
sf::Sprite Object::getSprite() {
	return sprite;
}

void TmxObject::draw(sf::RenderWindow& window) {
	window.draw(getSprite());
}

// PushButton methods///////////////////////////////////////////////////////////////////////////////////
PushButton::PushButton(std::string file,sf::FloatRect r, sf::Color b_color, sf::Color c_color) {
	rect = r;
	texture.loadFromFile(file);
	rect.width = texture.getSize().x;
	rect.height = texture.getSize().y;
	sprite.setTexture(texture, &rect);
	sprite.setPosition(rect.left, rect.top);
	base_color = b_color;
	clicked_color = c_color;
	is_clicked = false;
}
void PushButton::input(sf::RenderWindow& window) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (is_pos(window))
			State.CurrState = true;
	bool IsPressedAndReleased = State.pick();
	if (is_pos(window) && IsPressedAndReleased)
		std::invoke(OnClick);
}

void PushButton::update(sf::RenderWindow& window) {
	if (is_pos(window) || is_clicked) 
		sprite.setColor(clicked_color);
	else 
		sprite.setColor(base_color);
}

void PushButton::draw(sf::RenderWindow& window) {
	window.draw(getSprite());
}

bool  PushButton::is_pos(sf::RenderWindow& window) { // function: bool is mouse is possed at button rect
	sf::IntRect r(rect.left, rect.top, rect.width, rect.height);
	if (r.contains(sf::Mouse::getPosition(window)))
		return true;
	return false;
}

bool PushButton::ButtonClick::pick() {
	// Button is pushed in current frame.
	if (CurrState) {
		PrevState = true;
		CurrState = false;
		return false;
	}
	// Here CurrState is false (button released)
	if (PrevState) {// Prev frame button was pushed
		PrevState = false;
		CurrState = false;
		return true;
	}
	// Prev frame nothig happens
	PrevState = false;
	CurrState = false;
	return false;
}