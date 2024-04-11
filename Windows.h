#pragma once
#include<vector>
#include "Object.h"
#include "Player.h"
#include "GlobalState.h"
#include "TmxLevel.h"
#include "view.h"

void onExit();
void onStartGame();
void onSettings();
void onMenu();

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
    virtual void update(sf::RenderWindow& window) {
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
        auto* ExitBtn = new PushButton{ "images/exit256.png", 100, 700 };
        ExitBtn->registerFunction(onExit);
        Buttons.push_back(ExitBtn);

        auto* StartGameBtn = new PushButton{ "images/play256.png", 100, 100 };
        StartGameBtn->registerFunction(onStartGame);
        Buttons.push_back(StartGameBtn);

        auto* SettingsBtn = new PushButton{ "images/settings256.png", 100, 400 };
        SettingsBtn->registerFunction(onSettings);
        Buttons.push_back(SettingsBtn);
    }
};

class GameWindow final : public BaseWindow {
public:
    static constexpr auto Name = "game";
    Player p;
    //TmxLevel level;
    //Level lvl;//создали экземпл€р класса уровень
   
    GameWindow() {
        auto* MenuBtn = new PushButton{ "images/back256.png", 100, 700 };
        MenuBtn->registerFunction(onMenu);
        Buttons.push_back(MenuBtn);
        //lvl.LoadFromFile("map/map.tmx");//загрузили в него карту, внутри класса с помощью методов он ее обработает.
    }
    ~GameWindow() = default;
    void input(sf::RenderWindow& window) override {
        BaseWindow::input(window);
        p.input();
    }
    void update(sf::RenderWindow& window) override {
        BaseWindow::update(window);
        p.update();
    }
     void draw(sf::RenderWindow& window) override {
         BaseWindow::draw(window);
        // lvl.Draw(window);
         //sf::RenderTarget& target = view.window;
         //level.Draw(target);
         p.draw(window);

        
    }
};
class SettingsWindow final : public BaseWindow {
public:
    static constexpr auto Name = "settings";

    SettingsWindow() {
        auto* MenuBtn = new PushButton{ "images/back256.png", 100, 700 };
        MenuBtn->registerFunction(onMenu);
        Buttons.push_back(MenuBtn);
    }
};

