#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h";
#include "Windows.h"
//#include "View.h"
#include "Scene.h"

class Game{
private:

    sf::RenderWindow window;
    sf::View view;
    sf::Vector2f windowSize;
    sf::Clock clock;
    int frames;

    void input();
    void update();
    void draw();

public:
    Game();
    void start();  
    void SetCameraCenter(sf::RenderWindow& window, sf::View& view, const sf::Vector2f& center);
};
