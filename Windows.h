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
void onStartGame(int &level, int l);
void onPause(bool &is_pause);
void onSettings();
void onMenu();
void onLevel();

void downVolume(std::vector<sf::Music*> mvec);
void upVolume(std::vector<sf::Music*> mvec);

void updatePauseScreen(sf::View& view, std::vector<PushButton*>& Buttons, std::vector<Object*>& Objects);
void SetLevel(int level, int l, sf::Music* music, std::vector<sf::Music*> mvec, std::unique_ptr<GameScene> &gameScene);

void playMusic(sf::Music* music, std::vector<sf::Music*> mvec);

static std::vector<sf::Music*> MusicVector = {};
inline bool is_pause = false;
inline int lvl = 1;// уровень по умолчанию
inline constexpr int num_levels = 4;// кол-во уровней. изменить при добавлении нового уровня на +1. Также в levelWindow можно добавить соответствующую кнопку


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
    virtual void update(sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize, float loopTime) {
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
    sf::Music menuMusic;
    MenuWindow() {     
       
        menuMusic.openFromFile("audio/Pixel Music Pack/Ogg/Pixel 1.ogg");
        menuMusic.setLoop(true);
        MusicVector.push_back(&menuMusic);

        auto* background = new Object{ "images/Free Pixel Art Hill/ajys.png",0.f,0.f };
        Objects.push_back(background);
        
        auto* StartGameBtn = new PushButton{ "images/playBTN.png",sf::FloatRect(sf::Vector2f(100,200),sf::Vector2f()) };
        StartGameBtn->registerFunction(onStartGame, std::ref(lvl), 1);
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
    void update(sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize, float loopTime) override {
        if (MusicVector[0]->getStatus() != sf::Music::Playing) { //once when window changes
            playMusic(MusicVector[0], MusicVector);
            view.reset(sf::FloatRect(0.0f, 0.0f, windowSize.x, windowSize.y));
            is_pause = false;
        }
        BaseWindow::update(window, view, windowSize, loopTime);
    }
};

class GameWindow final : public BaseWindow {
public:
    static constexpr auto Name = "game1";
    std::unique_ptr<GameScene> gameScene;
    std::vector <sf::Music> gameMusic{num_levels+1};
    GameWindow() {
        for (int i = 0; i <= num_levels ; ++i) {
            gameMusic[i].openFromFile("audio/Pixel Music Pack/Ogg/Pixel " + std::to_string(i%12 + 1) +".ogg");
            gameMusic[i].setLoop(true);
            MusicVector.push_back(&gameMusic[i]);
        }
        SetLevel(lvl, 1, MusicVector[1], MusicVector, gameScene);

        auto* light = new Object{ "images/light.png", 0, 80 };
        Objects.push_back(light);


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
    ~GameWindow() = default;

    void input(sf::RenderWindow& window, sf::View & view) override {
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            if (!is_pause) is_pause = true;
        if (is_pause) 
            BaseWindow::input(window, view);
        gameScene.get()->InputGameScene(window);
    }
    void update(sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize, float loopTime) override {
        sf::Vector2f view_center = view.getCenter();
        Objects[0]->sprite.setPosition(view_center.x -  windowSize.x/2 +8, view_center.y - windowSize.y/2-8);
        if (is_pause) {
            updatePauseScreen(view, Buttons, Objects);
            BaseWindow::update(window, view, windowSize, loopTime);
            return;
        } 
        for (int i = 1; i <= num_levels; ++i) {
            SetLevel(lvl, i, &gameMusic[i], MusicVector, gameScene);
        }

        if(view.getSize().x != window.getSize().x / 2)
            view.setSize(window.getSize().x / 2, window.getSize().y / 2);
        gameScene->world.Step(timeStep, gameScene->velocityIterations, gameScene->positionIterations);
        gameScene.get()->UpdateGameScene(window, view, windowSize, lvl, loopTime);
    }
    void draw(sf::RenderWindow& window) override {
        gameScene.get()->DrawGameScene(window);
        Objects[0]->draw(window);
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
        volume_upBtn->registerFunction(upVolume, std::ref(MusicVector));
        Buttons.push_back(volume_upBtn);

        auto* volume_downBtn = new PushButton{ "images/sound_down.png", sf::FloatRect(sf::Vector2f(100,200),sf::Vector2f()) };
        volume_downBtn->registerFunction(downVolume, std::ref(MusicVector));
        Buttons.push_back(volume_downBtn);

        for (float i = 0; i < 10; ++i) {
            auto* box = new Object{ "images/wbox.png", 220 + 24*i, 228 };
            volume_set.push_back(box);
        }
    }
    void draw (sf::RenderWindow& window)override {
        BaseWindow::draw(window);
        
        float vol = MusicVector[0]->getVolume()/10.f;
        for (int i = 0; i < vol; ++i)
            volume_set[i]->draw(window);
    }
};

class LevelWindow final : public BaseWindow {
public:
    static constexpr auto Name = "level";
    std::vector<PushButton> pButtons{num_levels};
    LevelWindow() {
        auto* MenuBtn = new PushButton{ "images/backBTN.png", sf::FloatRect(sf::Vector2f(100,768),sf::Vector2f()) };
        MenuBtn->registerFunction(onMenu);
        Buttons.push_back(MenuBtn);
        for (int i = 1; i <= num_levels; ++i) {
            pButtons[i - 1].setButton(&pButtons[i - 1], "images/" + std::to_string(i) + ".png", sf::FloatRect(sf::Vector2f(100 + 200 * (i - 1), 100), sf::Vector2f()));
            pButtons[i - 1].registerFunction(onStartGame, std::ref(lvl), i);
            Buttons.push_back(&pButtons[i-1]);
        }
    }
};