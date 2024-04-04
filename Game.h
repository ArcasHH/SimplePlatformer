#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h";

class Game{
private:

    sf::RenderWindow window;

    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;

    Player player;

    void input();
    void update(float dtAsSeconds);
    void draw();

public:
    Game();
    void start();
};