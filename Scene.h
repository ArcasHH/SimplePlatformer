#pragma once
#include "Object.h"
#include "GlobalState.h"

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
void UpdateGameScene(void* pData, sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize, int &lvl);
void DrawGameScene(void* pData, sf::RenderWindow& window);
void DestroyGameScene(GameScene*& pScene);
static void SetCameraCenter(sf::RenderWindow& window, sf::View& view, const sf::Vector2f& center);