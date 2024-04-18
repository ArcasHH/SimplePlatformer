#pragma once
#include<vector>
#include "Object.h"
#include "GlobalState.h"
#include "TmxLevel.h"
#include "Scene.h"
#include <SFML/Audio.hpp>
void onExit();
void onStartGame1();
void onStartGame2();
void onSettings();
void onMenu();
void onLevel();
//void changeLevel();
static sf::Music menuMusic;
static sf::Music gameMusic;


class BaseWindow {
protected:
    std::vector<Object*> Objects;
    std::vector<PushButton*> Buttons;
public:
    BaseWindow() {};
    virtual ~BaseWindow() {
        for (auto* Obj : Objects)
            delete Obj;
        for (auto* Obj : Buttons)
            delete Obj;
    }
    virtual void input(sf::RenderWindow& window) {
        for (auto&& Obj : Buttons) {
            Obj->input(window);
        }
    }
    virtual void update(sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize, float deltaSec) {
        for (auto&& Obj : Buttons)
            Obj->update(window);
    }
    virtual void draw(sf::RenderWindow& window) {
        for (auto&& Obj : Objects)
            Obj->draw(window);
        for (auto&& Obj : Buttons)
            Obj->draw(window);
    }
};

class MenuWindow final : public BaseWindow {
public:
    static constexpr auto Name = "menu";

    MenuWindow() {     
        menuMusic.openFromFile("audio/Pixel Music Pack/Ogg/Pixel 1.ogg");
        menuMusic.setLoop(true);
        menuMusic.play();
        auto* background = new Object{ "images/Free Pixel Art Hill/ajys.png",0.f,0.f };
        Objects.push_back(background);
        
        auto* StartGameBtn = new PushButton{ "images/playBTN.png",sf::FloatRect(sf::Vector2f(96,128),sf::Vector2f()) };
        StartGameBtn->registerFunction(onStartGame1);
        Buttons.push_back(StartGameBtn);

        auto* LevelBtn = new PushButton{ "images/levelBTN.png", sf::FloatRect(sf::Vector2f(96,320),sf::Vector2f()) };
        LevelBtn->registerFunction(onLevel);
        Buttons.push_back(LevelBtn);

        auto* SettingsBtn = new PushButton{ "images/settingsBTN.png", sf::FloatRect(sf::Vector2f(96,512),sf::Vector2f()) };
        SettingsBtn->registerFunction(onSettings);
        Buttons.push_back(SettingsBtn);

        auto* ExitBtn = new PushButton{ "images/exitBTN.png", sf::FloatRect(sf::Vector2f(96,708),sf::Vector2f()) };
        ExitBtn->registerFunction(onExit);
        Buttons.push_back(ExitBtn);
    }
};

class GameWindow1 final : public BaseWindow {
public:
    static constexpr auto Name = "game1";
    DynamicObject p;
    GameScene* gameScene1;
    std::vector<TmxObject*> p_objects;
    GameWindow1() {
        gameScene1 = NewGameScene("map/platformer1.tmx");
        for (auto&& obj : gameScene1->blocks) {
            obj.setPhysics();
        }
        p = DynamicObject(gameScene1->player);
    }
    ~GameWindow1() = default;
    void input(sf::RenderWindow& window) override {
        world.Step(timeStep, velocityIterations, positionIterations);
        BaseWindow::input(window);
        InputGameScene(gameScene1, window);
    }
    void update(sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize, float deltaSec) override {
        if (menuMusic.getStatus() == sf::Music::Playing) {
            menuMusic.stop();
            gameMusic.openFromFile("audio/Pixel Music Pack/Ogg/Pixel 6.ogg");
            gameMusic.setLoop(true);
            gameMusic.play();
        }
        BaseWindow::update(window, view, windowSize, deltaSec);
        UpdateGameScene(gameScene1, window, view, windowSize, deltaSec);
    }
    void draw(sf::RenderWindow& window) override {
        BaseWindow::draw(window);
        DrawGameScene(gameScene1, window);
    }
};

class GameWindow2 final : public BaseWindow {
public:
    static constexpr auto Name = "game2";
    DynamicObject p;
    GameScene* gameScene2;
    std::vector<TmxObject*> p_objects;
    GameWindow2() {
        gameScene2 = NewGameScene("map/platformer2.tmx");
        for (auto&& obj : gameScene2->blocks) {
            obj.setPhysics();
        }
        p = DynamicObject(gameScene2->player);
    }
    ~GameWindow2() = default;
    void input(sf::RenderWindow& window) override {
        world.Step(timeStep, velocityIterations, positionIterations);
        BaseWindow::input(window);
        InputGameScene(gameScene2, window);
    }
    void update(sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize, float deltaSec) override {
        if (menuMusic.getStatus() == sf::Music::Playing) {
            menuMusic.stop();
            gameMusic.openFromFile("audio/Pixel Music Pack/Ogg/Pixel 9.ogg");
            gameMusic.setLoop(true);
            gameMusic.play();
        }
        BaseWindow::update(window, view, windowSize, deltaSec);
        UpdateGameScene(gameScene2, window, view, windowSize, deltaSec);
    }
    void draw(sf::RenderWindow& window) override {
        BaseWindow::draw(window);
        DrawGameScene(gameScene2, window);
    }
};

class SettingsWindow final : public BaseWindow {
public:
    static constexpr auto Name = "settings";

    SettingsWindow() {
        auto* MenuBtn = new PushButton{ "images/backBTN.png", sf::FloatRect(sf::Vector2f(100,768),sf::Vector2f() )};
        MenuBtn->registerFunction(onMenu);
        Buttons.push_back(MenuBtn);
    }
};

class LevelWindow final : public BaseWindow {
public:
    static constexpr auto Name = "level";

    LevelWindow() {
        auto* MenuBtn = new PushButton{ "images/backBTN.png", sf::FloatRect(sf::Vector2f(100,768),sf::Vector2f()) };
        MenuBtn->registerFunction(onMenu);
        Buttons.push_back(MenuBtn);
        auto* oneBtn = new PushButton{ "images/1.png", sf::FloatRect(sf::Vector2f(100,100),sf::Vector2f()) };
        oneBtn->registerFunction(onStartGame1);
        Buttons.push_back(oneBtn);
        auto* twoBtn = new PushButton{ "images/2.png", sf::FloatRect(sf::Vector2f(260,100),sf::Vector2f()) };
        twoBtn->registerFunction(onStartGame2);
        Buttons.push_back(twoBtn);
    }
};

