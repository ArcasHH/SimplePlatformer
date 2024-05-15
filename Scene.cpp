#include "Scene.h"
#include "Windows.h"
#include <math.h>

static const float PLAYER_SPEED = 10000000;
static float PLAYER_SPEED_FOR_FRAME = PLAYER_SPEED;

void GameScene::CreateStaticObjects() {
    auto& vec = blocks;
    for (int i = 0; i < vec.size(); ++i) {
        b2BodyDef bodyDef;
        
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set((vec[i].rect.left + (vec[i].rect.width) / 2),
            (vec[i].rect.top + (vec[i].rect.height) / 2));
        
        b2Body* body = world.CreateBody(&bodyDef); 
        b2PolygonShape shape;
        shape.SetAsBox(vec[i].rect.width / 2, vec[i].rect.height / 2);
        body->CreateFixture(&shape, 0.0f);
    }
}
void GameScene::CreateCoinsObjects() {
    for (int i = 0; i < coins.size(); ++i) {
        b2BodyDef bodyDef;

        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set((coins[i].rect.left + (coins[i].rect.width) / 2),
            (coins[i].rect.top - (coins[i].rect.height) / 2));
        //b2Body* body = world.CreateBody(&bodyDef);
        coinBodies.push_back(world.CreateBody(&bodyDef));
        b2PolygonShape shape;
        shape.SetAsBox(coins[i].rect.width / 2, coins[i].rect.height / 2);
        coinBodies[i]->CreateFixture(&shape, 0.0f);
        coins[i].start_pos = sf::Vector2f(coinBodies[i]->GetPosition().x, coinBodies[i]->GetPosition().y);
    }
}
void GameScene::CreatePlayerBody() {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set((player.rect.left + (player.rect.width) / 2),
        (player.rect.top - (player.rect.height) / 2));
    bodyDef.fixedRotation = true;

    playerBody = world.CreateBody(&bodyDef);
    b2PolygonShape shape; 
    shape.SetAsBox(player.rect.width / 2, player.rect.height / 2);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.f;
    fixtureDef.friction = 1.0f;
    playerBody->CreateFixture(&fixtureDef);
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

GameScene::GameScene(const std::string & file){
    level.LoadFromFile(file);
    player = level.GetFirstObject("player");
    player.start_pos = player.sprite.getPosition();
    CreatePlayerBody();
    coins = level.GetAllObjects("coin");
    CreateCoinsObjects();
    //pLogic->enemies = level.GetAllObjects("enemy");
    blocks = level.GetAllObjects("block");
    CreateStaticObjects();
}



void InputGameScene(GameScene* pLogic, sf::RenderWindow& window) {
    pLogic->world.Step(timeStep, pLogic->velocityIterations, pLogic->positionIterations);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        pLogic->playerBody->ApplyForceToCenter(b2Vec2(PLAYER_SPEED_FOR_FRAME, 0), true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
         pLogic->playerBody->ApplyForceToCenter(b2Vec2(-PLAYER_SPEED_FOR_FRAME, 0), true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        b2Vec2 linV = pLogic->playerBody->GetLinearVelocity();
        pLogic->playerBody->ApplyForceToCenter(b2Vec2(linV.x, linV.y - PLAYER_SPEED_FOR_FRAME*5), true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        pLogic->playerBody->ApplyForceToCenter(b2Vec2(0.f, PLAYER_SPEED_FOR_FRAME * 5), true);
    }      
}
void UpdateGameScene(GameScene* pLogic, sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize, int& lvl, int32 loopTime){
    PLAYER_SPEED_FOR_FRAME = PLAYER_SPEED * ( static_cast<float>(loopTime) + 1.f/frames);
    //world.SetGravity(b2Vec2(0.f, world.GetGravity().y * (static_cast<float>(loopTime))));
    pLogic->prev_x = pLogic->player.sprite.getPosition().x;
    pLogic->prev_y = pLogic->player.sprite.getPosition().y;
    b2Vec2 p = pLogic->playerBody->GetPosition();
    pLogic->player.MoveTo(sf::Vector2f(p.x - 8, p.y + 8));

    for (int i = 0; i < pLogic->coinBodies.size(); ++i) {
        b2Vec2 c = pLogic->coinBodies[i]->GetPosition();
        pLogic->coins[i].MoveTo(sf::Vector2f(c.x - 8 , c.y + 8));

        if (pLogic->coins[i].rect.intersects(pLogic->player.rect)) { // condition for passing the level
            pLogic->playerBody->SetTransform(b2Vec2(pLogic->player.start_pos.x, pLogic->player.start_pos.y), 0);
            pLogic->playerBody->SetLinearVelocity(b2Vec2(0.f, 0.f));
            for (int j = 0; j < pLogic->coinBodies.size(); ++j) {
                pLogic->coinBodies[j]->SetTransform(b2Vec2(pLogic->coins[j].start_pos.x, pLogic->coins[j].start_pos.y), 0);
            }
            if (lvl == num_levels)
                lvl = 1;
            else
                ++lvl;
            return;
        }
    }
    pLogic->ChangeTexture();
    view.setCenter(pLogic->player.sprite.getPosition().x, pLogic->player.sprite.getPosition().y);
}

void DrawGameScene(GameScene* pLogic, sf::RenderWindow &window){
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
void GameScene::SetSpriteTexture(std::string file) {
    player.texture.loadFromFile(file);
    player.sprite.setTexture(player.texture);
    player.sprite.setTextureRect(sf::IntRect(0,0, player.texture.getSize().x, player.texture.getSize().y) );
}
void GameScene::ChangeTexture() {
    float dx = player.sprite.getPosition().x - prev_x;
    float dy = player.sprite.getPosition().y - prev_y;

    if (dy < 0 && dx >=0) {
        SetSpriteTexture("images/hero/jump1.png");
        return;
    }
    if (dy < 0 && dx < 0) {
        SetSpriteTexture("images/hero/jump2.png");
        return;
    }
    if (dy > 0 && dx >= 0) {
        SetSpriteTexture("images/hero/fall1.png");
        return;
        
    }
    if (dy > 0 && dx < 0) {
        SetSpriteTexture("images/hero/fall2.png");
        return;
    }
    
    if (dy == 0 && dx < 0) {
        SetSpriteTexture("images/hero/left.png");
        return;
    }
    if (dy == 0 && dx >= 0) {
        SetSpriteTexture("images/hero/right.png");
        return;
    }
}