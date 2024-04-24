#include "Scene.h"
#include "Windows.h"
#include <math.h>

static const float PLAYER_SPEED = 100000;
void CreateStaticObjects(std::vector<TmxObject> vec, bool is_block = false) {
    for (int i = 0; i < vec.size(); ++i) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        if(is_block)
            bodyDef.position.Set((vec[i].rect.left + (vec[i].rect.width) / 2),
            (vec[i].rect.top + (vec[i].rect.height) / 2));
        else
            bodyDef.position.Set((vec[i].rect.left + (vec[i].rect.width) / 2),
                (vec[i].rect.top - (vec[i].rect.height) / 2));
        b2Body* body = world.CreateBody(&bodyDef);
        b2PolygonShape shape;
        shape.SetAsBox(vec[i].rect.width / 2, vec[i].rect.height / 2);
        body->CreateFixture(&shape, 0.0f);
    }
}
void CreatePlayerBody(GameScene* pLogic) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set((pLogic->player.rect.left + (pLogic->player.rect.width) / 2),
        (pLogic->player.rect.top - (pLogic->player.rect.height) / 2));
    bodyDef.fixedRotation = true;

    pLogic->playerBody = world.CreateBody(&bodyDef);
    b2PolygonShape shape; shape.SetAsBox(pLogic->player.rect.width / 2, pLogic->player.rect.height / 2);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 1.0f;
    pLogic->playerBody->CreateFixture(&fixtureDef);
}
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

GameScene* NewGameScene(std::string file){
    GameScene* pLogic = new GameScene;
    TmxLevel& level = pLogic->level;
    
    level.LoadFromFile(file);
    pLogic->player = level.GetFirstObject("player");
    CreatePlayerBody(pLogic);
    pLogic->coins = level.GetAllObjects("coin");
    CreateStaticObjects(pLogic->coins);
    //pLogic->enemies = level.GetAllObjects("enemy");
    pLogic->blocks = level.GetAllObjects("block");
    CreateStaticObjects(pLogic->blocks, true);
    return pLogic;
}



void InputGameScene(void* pData, sf::RenderWindow& window) {
    GameScene* pLogic = reinterpret_cast<GameScene*>(pData);
    world.Step(timeStep, velocityIterations, positionIterations);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        pLogic->playerBody->ApplyForceToCenter(b2Vec2(PLAYER_SPEED, 0), true);
        pLogic->state.right = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        pLogic->playerBody->ApplyForceToCenter(b2Vec2(-PLAYER_SPEED, 0), true);
        pLogic->state.left = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        b2Vec2 linV = pLogic->playerBody->GetLinearVelocity();
        pLogic->playerBody->ApplyForceToCenter(b2Vec2(linV.x, linV.y-PLAYER_SPEED*100), true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        pLogic->playerBody->ApplyForceToCenter(b2Vec2(0.f, PLAYER_SPEED), true);
    }      
}
void UpdateGameScene(void* pData, sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize){
    
    auto& Glob = getGlobalState();
    GameScene* pLogic = reinterpret_cast<GameScene*>(pData);
    if (pLogic->state.left) {
       // sf::Texture t;
        //pLogic->player.texture.loadFromFile("images/left.png");
        //pLogic->player.texture = t;
        //pLogic->player.sprite.setTexture(t);
       // pLogic->state.left = false;
    }
    if (pLogic->state.right) {
       // sf::Texture t;
        //t.loadFromFile("images/right.png");
        //pLogic->player.texture.loadFromFile("images/right.png");
       // pLogic->player.sprite.setTexture(t);
       // pLogic->state.right = false;
    }
    //pLogic->player.sprite.setTexture(pLogic->player.texture);
    b2Vec2 p = pLogic->playerBody->GetPosition();
    if (p.x >= 980 && p.y < 150) { // condition for passing the level
        pLogic->playerBody->SetTransform(b2Vec2(104.5, 72.5), 0);
        pLogic->playerBody->SetLinearVelocity(b2Vec2(0.f, 0.f));
        Glob.setCurrWindow(GameWindow2::Name);
        return;
    }
    float width = pLogic->player.rect.width;
    float height = pLogic->player.rect.height;
    pLogic->player.MoveTo(sf::Vector2f(p.x - width / 2, p.y + height / 2));
    view.setCenter(pLogic->player.sprite.getPosition().x, pLogic->player.sprite.getPosition().y);
}

void DrawGameScene(void* pData, sf::RenderWindow &window){
    GameScene* pLogic = reinterpret_cast<GameScene*>(pData);
    sf::RenderTarget& target = window;
    pLogic->level.Draw(target);
    for (const TmxObject& coin : pLogic->coins)
        target.draw(coin.sprite);
    for (const TmxObject& enemy : pLogic->enemies)
        target.draw(enemy.sprite);
    target.draw(pLogic->player.sprite);
}

void DestroyGameScene(GameScene*& pScene){
    delete pScene;
    pScene = nullptr;
}