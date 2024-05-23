#pragma once
#include "Object.h"

struct GameScene {
    static inline constexpr int frames = 120;
    GameScene(const std::string& file);
private:
    const float PLAYER_SPEED = 10000000.f;
    float PLAYER_SPEED_FOR_FRAME = PLAYER_SPEED;

    TmxLevel level;

    TmxObject player;
    float prev_x, prev_y;
    b2Body* playerBody;
    bool on_ground = false;

    std::vector<TmxObject> enemies;
    std::vector<b2Body*> enemyBodies;

    std::vector<TmxObject> coins;
    std::vector<b2Body*> coinBodies;

    std::vector<TmxObject> blocks;

    const int32 velocityIterations = 8;
    const int32 positionIterations = 3;
    b2Vec2 gravity{ 0.f, 1.f * frames };
    b2World world{ gravity };

public:
    void MovePlayerToStart();
    void Step();

    void CreateStaticObjects();
    void CreateDynamicObjects(std::vector<TmxObject> &vec, std::vector<b2Body*> &bodyvec, float fixture);
    void CreatePlayerBody();

    void SetSpriteTexture(std::string file);
    void ChangeTexture();

    void InputGameScene();
    void UpdateGameScene( sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize, int& lvl);
    void DrawGameScene( sf::RenderWindow& window);
};

