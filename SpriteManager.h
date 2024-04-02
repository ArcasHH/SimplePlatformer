#pragma once
#include <SFML/Graphics.hpp>

class SpriteManager {
public:
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::String name;
	sf::String file;
	int widthOfSprite;
	int heightOfSprite;
	SpriteManager(sf::String File, sf::String Name) {
		file = File;
		name = Name;
		image.loadFromFile("images/" + file);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
};