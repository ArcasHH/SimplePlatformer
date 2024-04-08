#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h";
#include "Windows.h"

class Game{
private:

    sf::RenderWindow window;
    bool w1;
    //Player player;
    int frames;

    void input();
    void update(float dtAsSeconds);
    void draw();

public:
    BaseWindow w;
    Game();
    void start();    
};