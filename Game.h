#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h";
#include "Resource.h"

class Game{
private:

    sf::RenderWindow window;
    isW is_w = isW();//по умолчанию включает меню
    int frames;

    void input();
    void update(float dtAsSeconds);
    void draw();

public:
    BaseWindow* w;
    Game();
    void start();    
};
