#pragma once
#include <SFML/Graphics.hpp>

#include <functional>

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

	sf::IntRect rect;
public:
	bool is_clicked;
	sf::Sprite getSprite() override;
	bool  is_pos(sf::RenderWindow& window);

	using OnClickFunc = std::function<void()>;
	OnClickFunc OnClick;

	PushButton(std::string file, int x, int y,
		sf::IntRect area = sf::IntRect(), sf::Color b_color = sf::Color::White, sf::Color c_color = sf::Color::Red);
	~PushButton() = default;

	void input(sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window) override;

	void registerFunction(OnClickFunc F) { OnClick = std::move(F); }
};