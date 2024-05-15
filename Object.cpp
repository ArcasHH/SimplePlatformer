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
void PushButton::setButton(PushButton *btn, std::string file, sf::FloatRect r, sf::Color b_color, sf::Color c_color) {
	
	btn->rect = r;
	btn->texture.loadFromFile(file);
	btn->rect.width = btn->texture.getSize().x;
	btn->rect.height = btn->texture.getSize().y;
	btn->sprite.setTexture(btn->texture, &btn->rect);
	btn->sprite.setPosition(btn->rect.left, btn->rect.top);
	btn->base_color = b_color;
	btn->clicked_color = c_color;
	btn->is_clicked = false;
}
void PushButton::input(sf::RenderWindow& window, sf::View& view) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (is_pos(window, view))
			State.CurrState = true;
	bool IsPressedAndReleased = State.pick();
	if (is_pos(window, view) && IsPressedAndReleased)
		std::invoke(OnClick);
}

void PushButton::update(sf::RenderWindow& window, sf::View& view) {
	if (is_pos(window, view) || is_clicked) 
		sprite.setColor(clicked_color);
	else 
		sprite.setColor(base_color);
}

void PushButton::draw(sf::RenderWindow& window) {
	window.draw(getSprite());
}

bool  PushButton::is_pos(sf::RenderWindow& window, sf::View &view) { // function: bool is mouse is possed at button rect
	
	float scale = window.getSize().x / view.getSize().x;
	sf::IntRect r(rect.left - (scale - 1) * (view.getCenter().x - view.getSize().x / 2),
		          rect.top - (scale - 1) * (view.getCenter().y - view.getSize().y / 2),
		          rect.width * scale, rect.height * scale);
	r.left *= scale;
	r.top *= scale;

	if (r.contains(sf::Mouse::getPosition(window)))
		return true;
	return false;
}

void PushButton::setPosition(float x, float y) {
	sprite.setPosition(x, y);
	rect.left = x;
	rect.top = y;
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