#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include <box2d/box2d.h>
#include <vector>
#include <map>

static const float SCALE = 32.f;
static const float DEG = 57.29578f;
static const float timeStep = 1.f / 60.f;
static const int32 velocityIterations = 6;
static const int32 positionIterations = 2;

static b2Vec2 gravity(0.f, 500.f);
static b2World world(gravity);
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
	bool  is_pos(sf::RenderWindow& window);

	using OnClickFunc = std::function<void()>;
	OnClickFunc OnClick;

	PushButton(std::string file, sf::FloatRect area = sf::FloatRect(), sf::Color b_color = sf::Color(200,157,100), sf::Color c_color = sf::Color(154, 182, 154));
	~PushButton() = default;

	void input(sf::RenderWindow& window);
	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window) override;

	void registerFunction(OnClickFunc F, int lvl = 1) {
		OnClick = std::move(F);
		level = lvl;
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
