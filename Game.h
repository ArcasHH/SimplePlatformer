#pragma once
#include <SFML/Graphics.hpp>
#include "Windows.h"
#include "GlobalState.h"

class Game{
private:

    sf::RenderWindow window;
    sf::View view;
    sf::Vector2f windowSize;
    sf::Clock clock;
public:
    Game();
    void start();  
};
