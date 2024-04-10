#pragma once
#include <SFML/Graphics.hpp>

class isW {
public:
	bool is_exit;
	bool is_menu ;
	bool is_settings;
	bool is_game;
	isW(bool e = false, bool m = true, bool s = false, bool g = false) {//по умолчанию меню
		is_exit = e;
		is_menu = m;
		is_settings = s;
		is_game = g;
	}
};
isW exit_button();
isW menu_button();
isW settings_button();
isW game_button();

class Object {
protected:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2i pos;
	sf::Vector2i size;
	
public:
	Object() {};
	Object(std::string file, int x, int y);
	virtual ~Object() = default;

	virtual sf::Sprite getSprite();
	
	//input();
	//update();
	virtual void draw(sf::RenderWindow& window);
};

class PushButton final : Object {
	
	sf::Color base_color;
	sf::Color clicked_color;

	isW w;//определяет св-ва кнопки
	sf::IntRect rect;
public:
	bool is_clicked;
	sf::Sprite getSprite() override;
	bool  is_pos(sf::RenderWindow& window);

	PushButton(std::string file, int x, int y, isW ww,
		sf::IntRect area = sf::IntRect(), sf::Color b_color = sf::Color::White, sf::Color c_color = sf::Color::Red);
	~PushButton() = default;

	void input(sf::RenderWindow& window, isW &is_w);
	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window) override;
};