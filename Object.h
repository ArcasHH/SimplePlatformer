#pragma once
#include <SFML/Graphics.hpp>

class isW {
public:
	bool is_exit;
	bool is_menu ;
	bool is_settings;
	isW(bool e = false, bool m = true, bool s = false) {
		is_exit = e;
		is_menu = m;
		is_settings = s;
	}
};
isW exit_button();
isW menu_button();
isW settings_button();

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
	virtual void draw(sf::RenderWindow& window);
};

class PushButton final : Object {
	
	sf::Color base_color;
	sf::Color clicked_color;
	//enum action {exit, menu, settings, next, restart, play, none} ;
	//bool is_exit, is_menu;
	isW w;
	sf::IntRect rect;
public:
	bool is_pointed, is_clicked;
	sf::Sprite getSprite();
	PushButton(std::string file, int x, int y, isW ww,
		sf::IntRect area = sf::IntRect(), sf::Color b_color = sf::Color::White, sf::Color c_color = sf::Color::Red);
	~PushButton() {};
	void input(sf::RenderWindow& window, isW &is_w);
	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window) override;
	bool  is_pos(sf::RenderWindow& window);
};