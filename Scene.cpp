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
/*
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
}*/

GameScene* NewGameScene(){
    GameScene* pLogic = new GameScene;
    TmxLevel& level = pLogic->level;
    
    level.LoadFromFile("map/platformer1.tmx");
    pLogic->player = level.GetFirstObject("player");
    pLogic->coins = level.GetAllObjects("coin");
    pLogic->enemies = level.GetAllObjects("enemy");
    pLogic->blocks = level.GetAllObjects("block");
    
    for (int i = 0; i < pLogic->blocks.size(); ++i)
    {
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set((pLogic->blocks[i].rect.left + (pLogic->blocks[i].rect.width)/2),
            (pLogic->blocks[i].rect.top + (pLogic->blocks[i].rect.height) / 2));
        b2Body* body = world.CreateBody(&bodyDef);
        b2PolygonShape shape;
        shape.SetAsBox(pLogic->blocks[i].rect.width / 2, pLogic->blocks[i].rect.height / 2);
        body->CreateFixture(&shape, 0.0f);
    }
    b2BodyDef bodyDef;

    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set((pLogic->player.rect.left + (pLogic->player.rect.width) / 2),
        (pLogic->player.rect.top + (pLogic->player.rect.height) / 2));
    bodyDef.fixedRotation = true;
    
    pLogic->playerBody = world.CreateBody(&bodyDef);
    b2PolygonShape shape; shape.SetAsBox(pLogic->player.rect.width / 2, pLogic->player.rect.height / 2);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f; 
    fixtureDef.friction = 1.0f;
    pLogic->playerBody->CreateFixture(&fixtureDef);
    return pLogic;
}
void InputGameScene(void* pData, sf::RenderWindow& window) {
    GameScene* pLogic = reinterpret_cast<GameScene*>(pData);
    world.Step(1.0f / 60.0f, 8, 3);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        //pLogic->playerBody->SetLinearVelocity(b2Vec2((pLogic->playerSpeed), 0.f));
        pLogic->playerBody->ApplyForceToCenter(b2Vec2((pLogic->playerSpeed), 100000.f), true);
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        //pLogic->playerBody->SetLinearVelocity(b2Vec2(-(pLogic->playerSpeed), 0.f));
        pLogic->playerBody->ApplyForceToCenter(b2Vec2(-(pLogic->playerSpeed), 100000.f), true);
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ) {
        //pLogic->playerBody->SetLinearVelocity(b2Vec2 ( 0.f, -(pLogic->playerSpeed)));
        pLogic->playerBody->ApplyLinearImpulseToCenter(b2Vec2(0.f, -(pLogic->playerSpeed)), true);
        return;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        //pLogic->playerBody->SetLinearVelocity(b2Vec2(0.f, (pLogic->playerSpeed)));
        pLogic->playerBody->ApplyLinearImpulseToCenter(b2Vec2(0.f, (pLogic->playerSpeed)), true);
        //return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        //pLogic->playerBody->SetLinearVelocity(b2Vec2 ( 0.f, -(pLogic->playerSpeed)));
        pLogic->playerBody->ApplyForceToCenter(b2Vec2(0.f, -(pLogic->playerImpulse)), true);
        //return;
    }
    
           
}
void UpdateGameScene(void* pData, sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize, float deltaSec){
    GameScene* pLogic = reinterpret_cast<GameScene*>(pData);
    (void)deltaSec;
    const sf::Time elapsedTime = g_clock.getElapsedTime();
    TmxObject& player = pLogic->player;
    std::vector<TmxObject> blocks = pLogic->blocks;
    //sf::Vector2f movement = Round(GetPlayerDirection() * PLAYER_SPEED * deltaSec);
    
    //player.MoveBy(movement);
    b2Vec2 p = pLogic->playerBody->GetPosition();
    float width = pLogic->player.rect.width;
    float height = pLogic->player.rect.height;
    player.MoveTo(sf::Vector2f(p.x-width/2, p.y+height/2));

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