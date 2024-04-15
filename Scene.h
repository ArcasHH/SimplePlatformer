#pragma once
#include "TmxLevel.h"

struct GameView;
class Game;
static sf::Clock g_clock;
struct GameScene{
    TmxLevel level;
    TmxObject player;
    std::vector<TmxObject> enemies;
    std::vector<TmxObject> coins;
    std::vector<TmxObject> blocks;//objects with collision
};

GameScene* NewGameScene();
void UpdateGameScene(void* pData, sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize, float deltaSec);
void DrawGameScene(void* pData, sf::RenderWindow& window);
void DestroyGameScene(GameScene*& pScene);
static void SetCameraCenter(sf::RenderWindow& window, sf::View& view, const sf::Vector2f& center);