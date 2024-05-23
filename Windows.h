#pragma once
#include<vector>
#include "Object.h"
#include "GlobalState.h"
#include "TmxLevel.h"
#include "Scene.h"
#include <SFML/Audio.hpp>
#include <map>

inline bool is_pause = false;
inline int lvl = 1;// уровень по умолчанию
inline constexpr int num_levels = 4;// кол-во уровней. изменить при добавлении нового уровня на +1. Также в levelWindow можно добавить соответствующую кнопку


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

class MenuWindow final : public BaseWindow {
    sf::Music menuMusic;
public:
    static constexpr auto Name = "menu";
    
    MenuWindow();
    void update(sf::RenderWindow& window, sf::View& view, const sf::Vector2f windowSize) override;
};

class GameWindow final : public BaseWindow {
    std::unique_ptr<GameScene> gameScene;
    std::vector <sf::Music> gameMusic{ num_levels + 1 };
public:
    static constexpr auto Name = "game1";

    GameWindow();

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
public:
    static constexpr auto Name = "level";
    LevelWindow();
};