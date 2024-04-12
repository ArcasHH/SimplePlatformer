#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h";
#include "Windows.h"
#include "Scene.h"

class Game{
private:

    sf::RenderWindow window;
    sf::View view;
    sf::Vector2f windowSize;
    sf::Clock clock;
    int frames;

public:
    Game();
    void start();  
};
