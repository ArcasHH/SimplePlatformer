#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <box2d/box2d.h>
#include <vector>
#include <map>




static std::string box_name = "box";

static int level;

class Object {
public:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::FloatRect rect;
	
	Object() {};
	Object(std::string file, float x, float y);
	virtual ~Object() = default;

	virtual sf::Sprite getSprite();
	//input();
	//update();
	virtual void draw(sf::RenderWindow& window);
};

class TmxObject : public Object {
public:

	std::string name;
	std::string type;
	std::map<std::string, std::string> properties;

	int GetPropertyInt(const std::string& propertyName);
	float GetPropertyFloat(const std::string& propertyName);
	std::string GetPropertyString(const std::string& propertyName);

	void MoveTo(const sf::Vector2f& position);
	TmxObject() {}
	//input();
	//update();
	virtual void draw(sf::RenderWindow& window) override;
};

class PushButton final : Object {
	
	struct ButtonClick final {
		bool PrevState = false;
		bool CurrState = false;
		bool pick();
	} State;

	sf::Color base_color;
	sf::Color clicked_color;

public:
	bool is_clicked;
	bool  is_pos(sf::RenderWindow& window, sf::View& view);
	using OnClickFunc = std::function<void()>;
	OnClickFunc OnClick;

	PushButton(std::string file, sf::FloatRect area = sf::FloatRect(), sf::Color b_color = sf::Color(200,157,100), sf::Color c_color = sf::Color(154, 182, 154));
	PushButton() {};
	void setButton(PushButton *btn, std::string file, sf::FloatRect r, sf::Color b_color = sf::Color(200, 157, 100), sf::Color c_color = sf::Color(154, 182, 154));
	~PushButton() = default;

	void input(sf::RenderWindow& window, sf::View& view);
	void update(sf::RenderWindow& window, sf::View& view);
	void draw(sf::RenderWindow& window) override;
	void setPosition(float x, float y);
	template <typename FuncTy, typename ...Args>
	void registerFunction(FuncTy &&F, Args &&...args) {
		auto&& Call = std::bind(std::forward<FuncTy>(F), std::forward<Args>(args)...);
		OnClick = std::move(Call);
	}
};


struct TmxLayer {
	sf::Uint8 opacity = 0;
	std::vector<sf::Sprite> tiles;
};

class TmxLevel {
public:
	bool LoadFromFile(const std::string& filepath);

	TmxObject GetFirstObject(const std::string& name) const;
	std::vector<TmxObject> GetAllObjects(const std::string& name) const;
	sf::Vector2i GetTileSize() const;
	float GetTilemapWidth() const;
	float GetTilemapHeight() const;
	sf::Vector2f GetTilemapSize() const;

	void Draw(sf::RenderTarget& target) const;

private:
	int m_width = 0;
	int m_height = 0;
	int m_tileWidth = 0;
	int m_tileHeight = 0;
	int m_firstTileID = 0;
	sf::Texture m_tilesetImage;
	std::vector<TmxObject> m_objects;
	std::vector<TmxLayer> m_layers;
};
