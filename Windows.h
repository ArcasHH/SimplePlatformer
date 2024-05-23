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

void updatePauseScreen(sf::View& view, std::vector<std::unique_ptr<PushButton>>& Buttons, std::vector<std::unique_ptr<Object>>& Objects);
void SetLevel(int level, int l, sf::Music* music, std::vector<sf::Music*> mvec, std::unique_ptr<GameScene> &gameScene);

void playMusic(sf::Music* music, std::vector<sf::Music*> mvec);

static std::vector<sf::Music*> MusicVector = {};
inline bool is_pause = false;
inline int lvl = 1;// уровень по умолчанию
inline constexpr int num_levels = 4;// кол-во уровней. изменить при добавлении нового уровня на +1. Также в levelWindow можно добавить соответствующую кнопку


class BaseWindow {
    std::string Name{};
protected:
    std::vector<std::unique_ptr<Object>> Objects{};
    std::vector<std::unique_ptr<PushButton>> Buttons{};
    
public:
    BaseWindow() = default;
    virtual ~BaseWindow() = default;
    
    virtual void input(const sf::RenderWindow& window, const sf::View& view) {
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
    sf::Music menuMusic;
    MenuWindow() {     
       
        menuMusic.openFromFile("audio/Pixel Music Pack/Ogg/Pixel 1.ogg");
        menuMusic.setLoop(true);
        MusicVector.push_back(&menuMusic);

        Objects.emplace_back(std::make_unique<Object>("images/Free Pixel Art Hill/ajys.png", 0.f, 0.f));

        auto &StartBtn = Buttons.emplace_back(std::make_unique<PushButton>("images/playBTN.png", sf::FloatRect(sf::Vector2f(100, 200), sf::Vector2f())));
        StartBtn->registerFunction(onStartGame, std::ref(lvl), 1);

        auto& LevelBtn = Buttons.emplace_back(std::make_unique<PushButton>("images/levelBTN.png", sf::FloatRect(sf::Vector2f(100, 350), sf::Vector2f())));
        LevelBtn->registerFunction(onLevel);

        auto& SettingsBtn = Buttons.emplace_back(std::make_unique<PushButton>("images/settingsBTN.png", sf::FloatRect(sf::Vector2f(100, 500), sf::Vector2f())));
        SettingsBtn->registerFunction(onSettings);

        auto& ExitBtn = Buttons.emplace_back(std::make_unique<PushButton>("images/exitBTN.png", sf::FloatRect(sf::Vector2f(100, 650), sf::Vector2f())));
        ExitBtn->registerFunction(onExit);
    }
    void update(sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize) override {
        if (MusicVector[0]->getStatus() != sf::Music::Playing) { //once when window changes
            playMusic(MusicVector[0], MusicVector);
            view.reset(sf::FloatRect(0.0f, 0.0f, windowSize.x, windowSize.y));
            is_pause = false;
        }
        BaseWindow::update(window, view, windowSize);
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

        Objects.emplace_back(std::make_unique<Object>("images/light.png", 0, 80));
        Objects.emplace_back(std::make_unique<Object>("images/line.png", 0, 80));

        auto& PlayBtn = Buttons.emplace_back(std::make_unique<PushButton>("images/play96.png", sf::FloatRect(sf::Vector2f(100, 128), sf::Vector2f())));
        PlayBtn->registerFunction(onPause, std::ref(is_pause));

        auto& MenuBtn = Buttons.emplace_back(std::make_unique<PushButton>("images/menu96.png", sf::FloatRect(sf::Vector2f(250, 128), sf::Vector2f())));
        MenuBtn->registerFunction(onMenu);

        auto& ExitBtn = Buttons.emplace_back(std::make_unique<PushButton>("images/exit96.png", sf::FloatRect(sf::Vector2f(550, 128), sf::Vector2f())));
        ExitBtn->registerFunction(onExit);
    }

    void input(const sf::RenderWindow& window, const sf::View & view) override {
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            if (!is_pause) is_pause = true;
        if (is_pause) 
            BaseWindow::input(window, view);
        gameScene->InputGameScene();
    }
    void update(sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize) override {
        sf::Vector2f view_center = view.getCenter();
        Objects[0]->sprite.setPosition(view_center.x -  windowSize.x/2 +8, view_center.y - windowSize.y/2-8);
        if (is_pause) {
            updatePauseScreen(view, Buttons, Objects);
            BaseWindow::update(window, view, windowSize);
            return;
        } 
        for (int i = 1; i <= num_levels; ++i) {
            SetLevel(lvl, i, &gameMusic[i], MusicVector, gameScene);
        }

        if(view.getSize().x != window.getSize().x / 2)
            view.setSize(window.getSize().x / 2, window.getSize().y / 2);
        gameScene->world.Step(timeStep, gameScene->velocityIterations, gameScene->positionIterations);
        gameScene->UpdateGameScene(window, view, windowSize, lvl);
    }
    void draw(sf::RenderWindow& window) override {
        gameScene.get()->DrawGameScene(window);
        Objects[0]->draw(window);
        if (is_pause)
           BaseWindow::draw(window);
    }
};

class SettingsWindow final : public BaseWindow {
    std::vector<std::unique_ptr<Object>> volume_set;
public:
    static constexpr auto Name = "settings";
    SettingsWindow() {

        auto& MenuBtn = Buttons.emplace_back(std::make_unique<PushButton>("images/backBTN.png", sf::FloatRect(sf::Vector2f(100, 768), sf::Vector2f())));
        MenuBtn->registerFunction(onMenu);

        auto& VolUp = Buttons.emplace_back(std::make_unique<PushButton>("images/sound_up.png", sf::FloatRect(sf::Vector2f(476, 200), sf::Vector2f())));
        VolUp->registerFunction(upVolume, std::ref(MusicVector));

        auto& VolDown = Buttons.emplace_back(std::make_unique<PushButton>("images/sound_down.png", sf::FloatRect(sf::Vector2f(100, 200), sf::Vector2f())));
        VolDown->registerFunction(downVolume, std::ref(MusicVector));

        for (float i = 0; i < 10; ++i)
            volume_set.emplace_back(std::make_unique<Object>("images/wbox.png", 220 + 24 * i, 228));
    }
    void draw (sf::RenderWindow& window) override {
        BaseWindow::draw(window);
        
        float vol = MusicVector[0]->getVolume()/10.f;
        for (int i = 0; i < vol; ++i)
            volume_set[i]->draw(window);
    }
};

class LevelWindow final : public BaseWindow {
public:
    static constexpr auto Name = "level";
    LevelWindow() {
        auto& MenuBtn = Buttons.emplace_back(std::make_unique<PushButton>("images/backBTN.png", sf::FloatRect(sf::Vector2f(100, 768), sf::Vector2f())));
        MenuBtn->registerFunction(onMenu);

        for (int i = 1; i <= num_levels; ++i) {
            auto& Btn = Buttons.emplace_back(std::make_unique<PushButton>("images/" + std::to_string(i) + ".png", sf::FloatRect(sf::Vector2f(100 + 200 * (i - 1), 100), sf::Vector2f())));
            Btn->registerFunction(onStartGame, std::ref(lvl), i);
        }
    }
};