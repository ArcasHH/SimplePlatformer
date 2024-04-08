#pragma once
#include <SFML/Graphics.hpp>
class Object {
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2i pos;
	sf::Vector2i size;
	
public:
	sf::Sprite getSprite();
	Object(std::string file, int x, int y);
	~Object() {};
	//void input();
	//void update();
	void draw(sf::RenderWindow& window);
};