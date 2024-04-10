#include "Object.h"
isW exit_button() {
	isW w(true, false);
	return w;
}
isW menu_button() {
	isW w;
	return w;
}
isW settings_button() {
	isW w(false, false, true);
	return w;
}
isW game_button() {
	isW w(false, false, false, true);
	return w;
}



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

PushButton::PushButton(std::string file, int x, int y, isW ww, sf::IntRect area, sf::Color b_color, sf::Color c_color) {
	w = ww;
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
	is_clicked = false;
	
}
void PushButton::input(sf::RenderWindow& window, isW &is_w) {
	if (is_pos(window) && !is_clicked) {
		
		sf::Time t = sf::milliseconds(100);
		while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::sleep(t);// ожидание пока не отпустишь кнопку
		}

		is_clicked = true;
		if (w.is_exit) {
			window.close();
		}
		else if (w.is_settings) {
			is_clicked = false;
			is_w.is_menu = false;
			is_w.is_settings = true;
			return;
		}
		else if (w.is_menu) {
			is_clicked = false;
			is_w.is_settings = false;
			is_w.is_menu = true;
			return;
		}
	}
}
void PushButton::update(sf::RenderWindow& window) {
	if (is_pos(window) || is_clicked) {
		sprite.setColor(clicked_color);
	}
	else if (!is_clicked && !is_pos(window))
		sprite.setColor(base_color);
}
void PushButton::draw(sf::RenderWindow& window) {
	window.draw(getSprite());
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