#pragma once
#include "Object.h"
#include "GlobalState.h"
static const float SCALE = 32.f;
static const float DEG = 57.29578f;
static int frames = 120;
static const float timeStep = 1.f / frames;


struct GameView;
class Game;
struct GameScene{
    GameScene(const std::string& file);

    TmxLevel level;
    TmxObject player;
    float prev_x, prev_y;
    b2Body* playerBody;
    std::vector<TmxObject> enemies;
    std::vector<b2Body*> enemyBodies;
    std::vector<TmxObject> coins;
    std::vector<b2Body*> coinBodies;
    std::vector<TmxObject> blocks;

    const int32 velocityIterations = 8;
    const int32 positionIterations = 3;
    b2Vec2 gravity{ 0.f, 1.f * frames };
    b2World world{ gravity };

    void CreateStaticObjects();
    void CreateCoinsObjects();
    void CreateEnemiesObjects();
    void CreatePlayerBody();



    void SetSpriteTexture(std::string file);
    void ChangeTexture();
};

void InputGameScene(GameScene* pData, sf::RenderWindow& window);
void UpdateGameScene(GameScene* pData, sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize, int &lvl, int32 loopTime);
void DrawGameScene(GameScene* pData, sf::RenderWindow& window);
void DestroyGameScene(GameScene*& pScene);
void SetCameraCenter(sf::RenderWindow& window, sf::View& view, const sf::Vector2f& center);