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
	
	sf::Color base_color;
	sf::Color clicked_color;
	//enum action {exit, menu, settings, next, restart, play, none} ;
	bool is_exit, is_menu;
	sf::IntRect rect;
public:
	bool is_pointed, is_clicked;
	sf::Sprite getSprite();
	PushButton(std::string file, int x, int y, bool exit = false, bool menu = false, 
		sf::IntRect area = sf::IntRect(), sf::Color b_color = sf::Color::White, sf::Color c_color = sf::Color::Red);
	~PushButton() {};
	void input(sf::RenderWindow& window, bool& is_w);
	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	bool  is_pos(sf::RenderWindow& window);
};