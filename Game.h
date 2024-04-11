#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h";
#include "Windows.h"
#include "View.h"
#include "Scene.h"

class Game{
private:

    sf::RenderWindow window;
    int frames;

    void input();
    void update();
    void draw();

public:
    Game();
    void start();    
};
