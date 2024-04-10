#pragma once
#include<vector>
#include "GlobalState.h"
#include "Object.h"
class BaseWindow {
protected:
    std::vector<Object*> Objects;
    std::vector<PushButton*> Buttons;
public:
    BaseWindow() {};
    virtual ~BaseWindow() {
        for (auto* O : Objects)
            delete O;
        for (auto* O : Buttons)
            delete O;
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

    static void onExit() {
        auto& Glob = getGlobalState();
        Glob.setCurrWindow("exit");
    }

    static void onStartGame() {
        auto& Glob = getGlobalState();
        Glob.setCurrWindow("game");
    }

    static void onSettings() {
        auto& Glob = getGlobalState();
        Glob.setCurrWindow("settings");
    }

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
    static void onMenu() {
        auto& Glob = getGlobalState();
        Glob.setCurrWindow("menu");
    }

public:
    static constexpr auto Name = "game";
    Player p;
    GameWindow() {
        auto* MenuBtn = new PushButton{ "images/back256.png", 100, 700 };
        MenuBtn->registerFunction(onMenu);
        Buttons.push_back(MenuBtn);
        Objects.push_back(new Object{ "images/die.jpg", 100, 100 });
    }
    ~GameWindow() = default;
    void input(sf::RenderWindow& window) override {
        BaseWindow::input(window);
        p.input();
    }
    void update(sf::RenderWindow& window) override {
        for (auto&& Obj : Buttons)
            Obj->update(window);
        p.update();
        
    }
     void draw(sf::RenderWindow& window) override {
        for (auto&& Obj : Objects)
            Obj->draw(window);
        for (auto&& Obj : Buttons)
            Obj->draw(window);
        p.draw(window);
    }
};
class SettingsWindow final : public BaseWindow {

    static void onMenu() {
        auto& Glob = getGlobalState();
        Glob.setCurrWindow("menu");
    }

public:
    static constexpr auto Name = "settings";

    SettingsWindow() {
        auto* MenuBtn = new PushButton{ "images/back256.png", 100, 700 };
        MenuBtn->registerFunction(onMenu);
        Buttons.push_back(MenuBtn);
    }
};