#include "Scene.h"
#include <math.h>

static const float PLAYER_SPEED = 200;

static sf::Vector2f Normalize(const sf::Vector2f& value){
    const float length = std::hypotf(value.x, value.y);
    if (length < FLT_EPSILON){
        return sf::Vector2f(0, 0);
    }
    return value / length;
}

static sf::Vector2f Round(const sf::Vector2f& value){
    return sf::Vector2f(roundf(value.x), roundf(value.y));
}

static sf::Vector2f GetPlayerDirection(){
    sf::Vector2f direction;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        direction.y = -1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        direction.y = +1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        direction.x = -1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        direction.x = +1;
    }
    return Normalize(direction);
}

GameScene* NewGameScene(){
    GameScene* pLogic = new GameScene;
    TmxLevel& level = pLogic->level;
    
    level.LoadFromFile("map/platformer1.tmx");
    pLogic->player = level.GetFirstObject("player");
    pLogic->coins = level.GetAllObjects("coin");
    pLogic->enemies = level.GetAllObjects("enemy");

    return pLogic;
}

void UpdateGameScene(void* pData, sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize, float deltaSec){
    GameScene* pLogic = reinterpret_cast<GameScene*>(pData);
    (void)deltaSec;

    TmxObject& player = pLogic->player;
    const sf::Vector2f movement = Round(GetPlayerDirection() * PLAYER_SPEED * deltaSec);
    player.MoveBy(movement);

    SetCameraCenter( window, view, player.sprite.getPosition() + sf::Vector2f(windowSize.x / 4, windowSize.y / 4));
}

void DrawGameScene(void* pData, sf::RenderWindow &window){
    GameScene* pLogic = reinterpret_cast<GameScene*>(pData);
    sf::RenderTarget& target = window;
    pLogic->level.Draw(target);
    for (const TmxObject& coin : pLogic->coins){
        target.draw(coin.sprite);
    }
    for (const TmxObject& enemy : pLogic->enemies){
        target.draw(enemy.sprite);
    }
    //sf::Texture hero_texture;
    target.draw(pLogic->player.sprite);
}

void DestroyGameScene(GameScene*& pScene){
    delete pScene;
    pScene = nullptr;
}

void SetCameraCenter(sf::RenderWindow& window, sf::View& view, const sf::Vector2f& center) {
    view.setCenter(center.x, center.y);
    window.setView(view);
}