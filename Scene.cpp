#include "Scene.h"
#include "Windows.h"
#include <math.h>

static const float PLAYER_SPEED = 10000000;
static float PLAYER_SPEED_FOR_FRAME = PLAYER_SPEED;

void GameScene::CreateStaticObjects() {
    for (auto&& block : blocks) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set((block.rect.left + (block.rect.width) / 2), block.rect.top + (block.rect.height) / 2);
        b2Body* body = world.CreateBody(&bodyDef);
        b2PolygonShape shape;
        shape.SetAsBox(block.rect.width / 2, block.rect.height / 2);
        body->CreateFixture(&shape, 0.0f);
    }
}
void GameScene::CreateDynamicObjects(std::vector<TmxObject> &vec, std::vector<b2Body*> &bodyvec, float fixture) {
    for (int i = 0; i < vec.size(); ++i) {
        b2BodyDef bodyDef;
        
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set((vec[i].rect.left + (vec[i].rect.width) / 2),
            (vec[i].rect.top - (vec[i].rect.height) / 2));
        bodyvec.push_back(world.CreateBody(&bodyDef));
        b2PolygonShape shape;
        shape.SetAsBox(vec[i].rect.width / 2, vec[i].rect.height / 2);
        bodyvec[i]->CreateFixture(&shape,fixture);
        vec[i].start_pos = sf::Vector2f(bodyvec[i]->GetPosition().x, bodyvec[i]->GetPosition().y);
    }
}

void GameScene::CreatePlayerBody() {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(player.rect.left + (player.rect.width) / 2, player.rect.top - (player.rect.height) / 2);
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
    CreateDynamicObjects(coins, coinBodies, 0.f);

    enemies = level.GetAllObjects("enemy");
    CreateDynamicObjects(enemies, enemyBodies, 1.f);

    blocks = level.GetAllObjects("block");
    CreateStaticObjects();
}



void GameScene::InputGameScene(sf::RenderWindow& window) {
    world.Step(timeStep, velocityIterations, positionIterations);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        playerBody->ApplyForceToCenter(b2Vec2(PLAYER_SPEED_FOR_FRAME, 0), true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
         playerBody->ApplyForceToCenter(b2Vec2(-PLAYER_SPEED_FOR_FRAME, 0), true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        b2Vec2 linV = playerBody->GetLinearVelocity();
        playerBody->ApplyForceToCenter(b2Vec2(linV.x, linV.y - PLAYER_SPEED_FOR_FRAME*5), true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        playerBody->ApplyForceToCenter(b2Vec2(0.f, PLAYER_SPEED_FOR_FRAME * 5), true);
    }      
}
void GameScene::UpdateGameScene( sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize, int& lvl, int32 loopTime){
    PLAYER_SPEED_FOR_FRAME = PLAYER_SPEED * ( static_cast<float>(loopTime) + 1.f/frames);
    //world.SetGravity(b2Vec2(0.f, world.GetGravity().y * (static_cast<float>(loopTime))));
    prev_x = player.sprite.getPosition().x;
    prev_y = player.sprite.getPosition().y;
    b2Vec2 p = playerBody->GetPosition();
    player.MoveTo(sf::Vector2f(p.x - 8, p.y + 8));
    for (int i = 0; i < enemyBodies.size(); ++i) {
        b2Vec2 c = enemyBodies[i]->GetPosition();
        enemies[i].MoveTo(sf::Vector2f(c.x - 8, c.y + 8));
    }
    for (int i = 0; i < coinBodies.size(); ++i) {
        b2Vec2 c = coinBodies[i]->GetPosition();
        coins[i].MoveTo(sf::Vector2f(c.x - 8 , c.y + 8));

        if (coins[i].rect.intersects(player.rect)) { // condition for passing the level
            playerBody->SetTransform(b2Vec2(player.start_pos.x, player.start_pos.y), 0);
            playerBody->SetLinearVelocity(b2Vec2(0.f, 0.f));
            for (int j = 0; j < coinBodies.size(); ++j) {
                coinBodies[j]->SetTransform(b2Vec2(coins[j].start_pos.x,coins[j].start_pos.y), 0);
            }
            if (lvl == num_levels)
                lvl = 1;
            else
                ++lvl;
            return;
        }
    }
    ChangeTexture();
    view.setCenter(player.sprite.getPosition().x, player.sprite.getPosition().y);
}

void GameScene::DrawGameScene( sf::RenderWindow &window){
   //sf::RenderTarget& target = window;
   level.Draw(window);
    for (const TmxObject& coin : coins)
        window.draw(coin.sprite);
    for (const TmxObject& enemy : enemies)
        window.draw(enemy.sprite);
    window.draw(player.sprite);
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