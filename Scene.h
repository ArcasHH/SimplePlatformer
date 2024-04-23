#pragma once
#include "Object.h"
#include "GlobalState.h"

struct GameView;
class Game;
static sf::Clock g_clock;
struct GameScene{
    TmxLevel level;
    TmxObject player;
    PlayerStates state;
    b2Body* playerBody;
    std::vector<TmxObject> enemies;
    std::vector<TmxObject> coins;
    std::vector<b2Body*> coinBodies;
    std::vector<TmxObject> blocks;
    float playerSpeed = 1000000.f;
    float playerForce = 1000.f;
    float playerImpulse = 1000000.f;
    bool playerOnGround = false;
};

GameScene* NewGameScene(std::string file);
void InputGameScene(void* pData, sf::RenderWindow& window);
void UpdateGameScene(void* pData, sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize);
void DrawGameScene(void* pData, sf::RenderWindow& window);
void DestroyGameScene(GameScene*& pScene);
static void SetCameraCenter(sf::RenderWindow& window, sf::View& view, const sf::Vector2f& center);