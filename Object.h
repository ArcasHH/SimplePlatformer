#pragma once
#include <SFML/Graphics.hpp>
class Object {
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2i pos;
	sf::Vector2i size;
	
public:
	sf::Sprite getSprite();
	Object(std::string file, int x, int y);
	Object() {};
	virtual ~Object() {};
	//void input();
	//void update();
	void draw(sf::RenderWindow& window);
};

class PushButton : Object {
	bool is_pointed, is_clicked;
	sf::Color base_color;
	sf::Color clicked_color;
	enum action {exit, menu, settings, next, restart, play, none} ;
	sf::IntRect rect;
public:
	sf::Sprite getSprite();
	PushButton(std::string file, int x, int y, sf::IntRect area = sf::IntRect(), sf::Color b_color = sf::Color::White, sf::Color c_color = sf::Color::Red);
	~PushButton() {};
	//void input();
	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	bool  is_pos(sf::RenderWindow& window);
};