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
void downVolume();
void upVolume();
//void changeLevel();
static sf::Music menuMusic;
static sf::Music gameMusic;


class BaseWindow {
protected:
    std::vector<Object*> Objects;
    std::vector<PushButton*> Buttons;
    
public:
    std::string Name;
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
    virtual void update(sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize) {
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
    GameScene* gameScene1;
    GameWindow1() {
        gameScene1 = NewGameScene("map/platformer1.tmx");
    }
    ~GameWindow1() = default;
    void input(sf::RenderWindow& window) override {
        BaseWindow::input(window);
        InputGameScene(gameScene1, window);
    }
    void update(sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize) override {
        if (menuMusic.getStatus() == sf::Music::Playing) {
            menuMusic.stop();
            gameMusic.openFromFile("audio/Pixel Music Pack/Ogg/Pixel 6.ogg");
            gameMusic.setLoop(true);
            gameMusic.play();
        }
        world.Step(timeStep, velocityIterations, positionIterations);
        BaseWindow::update(window, view, windowSize);
        UpdateGameScene(gameScene1, window, view, windowSize);
    }
    void draw(sf::RenderWindow& window) override {
        BaseWindow::draw(window);
        DrawGameScene(gameScene1, window);
    }
};

class GameWindow2 final : public BaseWindow {
public:
    static constexpr auto Name = "game2";
    GameScene* gameScene2;
    GameWindow2() {
        gameScene2 = NewGameScene("map/platformer2.tmx");
    }
    ~GameWindow2() = default;
    void input(sf::RenderWindow& window) override {
        world.Step(timeStep, velocityIterations, positionIterations);
        BaseWindow::input(window);
        InputGameScene(gameScene2, window);
    }
    void update(sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize) override {
        if (menuMusic.getStatus() == sf::Music::Playing) {
            menuMusic.stop();
            gameMusic.openFromFile("audio/Pixel Music Pack/Ogg/Pixel 9.ogg");
            gameMusic.setLoop(true);
            gameMusic.play();
        }
        BaseWindow::update(window, view, windowSize);
        UpdateGameScene(gameScene2, window, view, windowSize);
    }
    void draw(sf::RenderWindow& window) override {
        BaseWindow::draw(window);
        DrawGameScene(gameScene2, window);
    }
};

class SettingsWindow final : public BaseWindow {
    std::vector<Object*> volume_set;
public:
    static constexpr auto Name = "settings";

    SettingsWindow() {
        auto* MenuBtn = new PushButton{ "images/backBTN.png", sf::FloatRect(sf::Vector2f(100,768),sf::Vector2f() )};
        MenuBtn->registerFunction(onMenu);
        Buttons.push_back(MenuBtn);
        auto* volume_upBtn = new PushButton{ "images/sound_up.png", sf::FloatRect(sf::Vector2f(476,200),sf::Vector2f()) };
        volume_upBtn->registerFunction(upVolume);
        Buttons.push_back(volume_upBtn);
        auto* volume_downBtn = new PushButton{ "images/sound_down.png", sf::FloatRect(sf::Vector2f(100,200),sf::Vector2f()) };
        volume_downBtn->registerFunction(downVolume);
        Buttons.push_back(volume_downBtn);

        for (float i = 0; i < 10; ++i) {
            auto* box = new Object{ "images/wbox.png", 220 + 24*i, 228 };
            Objects.push_back(box);
            volume_set.push_back(box);
        }
    }
    void draw (sf::RenderWindow& window)override {
        for (auto&& Obj : Buttons)
            Obj->draw(window);
        float vol = menuMusic.getVolume()/10.f;
        for (int i = 0; i < vol; ++i) {
            volume_set[i]->draw(window);
        }
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
        auto* twoBtn = new PushButton{ "images/2.png", sf::FloatRect(sf::Vector2f(300,100),sf::Vector2f()) };
        twoBtn->registerFunction(onStartGame2);
        Buttons.push_back(twoBtn);
    }
};

static void upVolume() {
    if (menuMusic.getVolume() <= 90) {
        menuMusic.setVolume(menuMusic.getVolume() + 10.f);
        gameMusic.setVolume(gameMusic.getVolume() + 10.f);
    }
   
}
static void downVolume() {
    if (menuMusic.getVolume() >= 10) {
        menuMusic.setVolume(menuMusic.getVolume() - 10.f);
        gameMusic.setVolume(gameMusic.getVolume() - 10.f);
    }
}