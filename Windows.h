#pragma once
#include<vector>
#include "Object.h"
#include "GlobalState.h"
#include "TmxLevel.h"
#include "Scene.h"
#include <SFML/Audio.hpp>
#include <map>

class BaseWindow {
protected:
    std::vector<std::unique_ptr<Object>> Objects{};
    std::vector<std::unique_ptr<PushButton>> Buttons{};
public:
    BaseWindow() = default;
    virtual ~BaseWindow() = default;
    
    virtual void input(const sf::RenderWindow& window, const sf::View& view);
    virtual void update(sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize);
    virtual void draw(sf::RenderWindow& window);
};

class GameWindow;
class MenuWindow final : public BaseWindow {
    GameWindow& GW;
    sf::Music menuMusic;
public:
    static constexpr auto Name = "menu";
    
    MenuWindow(GameWindow&);
    void update(sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize) override;
};

class GameWindow final : public BaseWindow {
public:
    static inline constexpr int num_levels = 4;// кол-во уровней. изменить при добавлении нового уровня на +1. Также в levelWindow можно добавить соответствующую кнопку
private:
    std::unique_ptr<GameScene> gameScene;
    std::vector <sf::Music> gameMusic{ num_levels };
    int CurrLvl = 1;
    bool IsPause = false;
public:
    static constexpr auto Name = "game1";

    GameWindow();

    auto& getCurrLvl() { return CurrLvl; }
    auto& getPause() { return IsPause; }

    void input(const sf::RenderWindow& window, const sf::View& view) override;
    void update(sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize) override;
    void draw(sf::RenderWindow& window) override;
};

class SettingsWindow final : public BaseWindow {
    std::vector<std::unique_ptr<Object>> volume_set;
public:
    static constexpr auto Name = "settings";
    SettingsWindow();
    void draw(sf::RenderWindow& window) override;
};

class LevelWindow final : public BaseWindow {
    GameWindow& GW;
public:
    static constexpr auto Name = "level";
    LevelWindow(GameWindow &GW);
};