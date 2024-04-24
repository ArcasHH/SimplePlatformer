#pragma once
#include<vector>
#include "Object.h"
#include "GlobalState.h"
#include "TmxLevel.h"
#include "Scene.h"
#include <SFML/Audio.hpp>
#include <map>
//buttons functional:
void onExit();
void onStartGame1();
void onStartGame2();
void onPause(bool &is_pause);
void onSettings();
void onMenu();
void onLevel();
void downVolume();
void upVolume();

void updatePauseScreen(sf::View& view, std::vector<PushButton*>& Buttons, std::vector<Object*>& Objects);

// music
static sf::Music menuMusic;
static sf::Music gameMusic1;
static sf::Music gameMusic2;
static std::vector<sf::Music*> MusicVector = { &menuMusic, &gameMusic1 , &gameMusic2 };
void playMusic(sf::Music& music, std::vector<sf::Music*> musicvec);

static bool is_pause = false;

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
    virtual void input(sf::RenderWindow& window, sf::View& view) {
        for (auto&& Obj : Buttons) 
            Obj->input(window, view);
    }
    virtual void update(sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize) {
        for (auto&& Obj : Buttons)
            Obj->update(window, view);
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

        auto* background = new Object{ "images/Free Pixel Art Hill/ajys.png",0.f,0.f };
        Objects.push_back(background);
        
        auto* StartGameBtn = new PushButton{ "images/playBTN.png",sf::FloatRect(sf::Vector2f(100,200),sf::Vector2f()) };
        StartGameBtn->registerFunction(onStartGame1);
        Buttons.push_back(StartGameBtn);

        auto* LevelBtn = new PushButton{ "images/levelBTN.png", sf::FloatRect(sf::Vector2f(100,350),sf::Vector2f()) };
        LevelBtn->registerFunction(onLevel);
        Buttons.push_back(LevelBtn);

        auto* SettingsBtn = new PushButton{ "images/settingsBTN.png", sf::FloatRect(sf::Vector2f(100,500),sf::Vector2f()) };
        SettingsBtn->registerFunction(onSettings);
        Buttons.push_back(SettingsBtn);

        auto* ExitBtn = new PushButton{ "images/exitBTN.png", sf::FloatRect(sf::Vector2f(100,650),sf::Vector2f()) };
        ExitBtn->registerFunction(onExit);
        Buttons.push_back(ExitBtn);
    }
    void update(sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize) override {
        if (menuMusic.getStatus() != sf::Music::Playing) { //once when window changes
            playMusic(menuMusic, MusicVector);
            view.reset(sf::FloatRect(0.0f, 0.0f, windowSize.x, windowSize.y));
            is_pause = false;
        }
        BaseWindow::update(window, view, windowSize);
    }
};

class GameWindow1 final : public BaseWindow {
public:
    static constexpr auto Name = "game1";
    
    GameScene* gameScene1;
    GameWindow1() {
        gameScene1 = NewGameScene("map/lvl1.tmx");
        gameMusic1.openFromFile("audio/Pixel Music Pack/Ogg/Pixel 9.ogg");
        gameMusic1.setLoop(true);
        auto* box = new Object{ "images/line.png", 0, 80 };
        Objects.push_back(box);

        auto* playBtn = new PushButton{ "images/play96.png", sf::FloatRect(sf::Vector2f(100,128),sf::Vector2f()) };
        playBtn->registerFunction(onPause, std::ref(is_pause));
        Buttons.push_back(playBtn);

        auto* MenuBtn = new PushButton{ "images/menu96.png", sf::FloatRect(sf::Vector2f(250,128),sf::Vector2f()) };
        MenuBtn->registerFunction(onMenu);
        Buttons.push_back(MenuBtn);

        auto* ExitBtn = new PushButton{ "images/exit96.png", sf::FloatRect(sf::Vector2f(550,128),sf::Vector2f()) };
        ExitBtn->registerFunction(onExit);
        Buttons.push_back(ExitBtn);
    }
    ~GameWindow1() = default;

    void input(sf::RenderWindow& window, sf::View & view) override {
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            if (!is_pause) is_pause = true;
        if (is_pause) 
            BaseWindow::input(window, view);
        InputGameScene(gameScene1, window);
    }
    void update(sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize) override {
        if (is_pause) {
            updatePauseScreen(view, Buttons, Objects);
            BaseWindow::update(window, view, windowSize);
            return;
        }   
        if (gameMusic1.getStatus() != sf::Music::Playing) {
            playMusic(gameMusic1, MusicVector);
            view.setSize(window.getSize().x / 2, window.getSize().y / 2);
            gameScene1->playerBody->SetTransform(b2Vec2(35, 135), 0.f);//initial position of the player
        }
        world.Step(timeStep, velocityIterations, positionIterations);
        UpdateGameScene(gameScene1, window, view, windowSize);
    }
    void draw(sf::RenderWindow& window) override {
        DrawGameScene(gameScene1, window);
        if (is_pause)
            BaseWindow::draw(window);
    }
};

class GameWindow2 final : public BaseWindow {
public:
    static constexpr auto Name = "game2";

    GameScene* gameScene2;
    GameWindow2() {
        gameScene2 = NewGameScene("map/lvl2.tmx");
        gameMusic2.openFromFile("audio/Pixel Music Pack/Ogg/Pixel 6.ogg");
        gameMusic2.setLoop(true);
        auto* box = new Object{ "images/line.png", 0, 80 };
        Objects.push_back(box);

        auto* playBtn = new PushButton{ "images/play96.png", sf::FloatRect(sf::Vector2f(100,128),sf::Vector2f()) };
        playBtn->registerFunction(onPause, std::ref(is_pause));
        Buttons.push_back(playBtn);

        auto* MenuBtn = new PushButton{ "images/menu96.png", sf::FloatRect(sf::Vector2f(250,128),sf::Vector2f()) };
        MenuBtn->registerFunction(onMenu);
        Buttons.push_back(MenuBtn);

        auto* ExitBtn = new PushButton{ "images/exit96.png", sf::FloatRect(sf::Vector2f(550,128),sf::Vector2f()) };
        ExitBtn->registerFunction(onExit);
        Buttons.push_back(ExitBtn);
    }
    ~GameWindow2() = default;

    void input(sf::RenderWindow& window, sf::View& view) override {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            if (!is_pause) is_pause = true;
        }
        if (is_pause)
            BaseWindow::input(window, view);
        else 
            InputGameScene(gameScene2, window);
    }
    void update(sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize) override {
        if (is_pause) {
            updatePauseScreen(view, Buttons, Objects);
            BaseWindow::update(window, view, windowSize);
            return;
        }
        if (gameMusic2.getStatus() != sf::Music::Playing) {
            playMusic(gameMusic2, MusicVector);
            view.setSize(window.getSize().x / 2, window.getSize().y / 2);
            gameScene2->playerBody->SetTransform(b2Vec2(35, 135), 0.f);
        }
        world.Step(timeStep, velocityIterations, positionIterations);
        UpdateGameScene(gameScene2, window, view, windowSize);
    }
    void draw(sf::RenderWindow& window) override {
        DrawGameScene(gameScene2, window);
        if (is_pause)
            BaseWindow::draw(window);
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
            volume_set.push_back(box);
        }
    }
    void draw (sf::RenderWindow& window)override {
        BaseWindow::draw(window);
        float vol = menuMusic.getVolume()/10.f;
        for (int i = 0; i < vol; ++i)
            volume_set[i]->draw(window);
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
    for (auto&& m : MusicVector) {
        float vol = m->getVolume();
        if (vol <= 90)
            m->setVolume(vol + 10.f);
    }
}
static void downVolume() {
    for (auto&& m : MusicVector) {
        float vol = m->getVolume();
        if ( vol >= 10)
            m->setVolume(vol - 10.f);
    }
}


 