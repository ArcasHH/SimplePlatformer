#pragma once
#include "Object.h"
#include "GlobalState.h"
static const float SCALE = 32.f;
static const float DEG = 57.29578f;
static int frames = 120;
static const float timeStep = 1.f / frames;
static const int32 velocityIterations = 8;
static const int32 positionIterations = 3;
static b2Vec2 gravity(0.f, 1.f*frames);
static b2World world(gravity);

struct GameView;
class Game;
struct GameScene{
    TmxLevel level;
    TmxObject player;
    float prev_x, prev_y;
    b2Body* playerBody;
    std::vector<TmxObject> enemies;
    std::vector<TmxObject> coins;
    std::vector<b2Body*> coinBodies;
    std::vector<TmxObject> blocks;
    void SetSpriteTexture(std::string file);
    void ChangeTexture();
};

GameScene* NewGameScene(std::string file);
void InputGameScene(void* pData, sf::RenderWindow& window);
void UpdateGameScene(void* pData, sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize, int &lvl, int32 loopTime);
void DrawGameScene(void* pData, sf::RenderWindow& window);
void DestroyGameScene(GameScene*& pScene);
void SetCameraCenter(sf::RenderWindow& window, sf::View& view, const sf::Vector2f& center);