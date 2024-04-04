#include "Game.h"

Game::Game(){
    //window
    sf::Vector2f resolution;
    resolution.x = sf::VideoMode::getDesktopMode().width;
    resolution.y = sf::VideoMode::getDesktopMode().height;
    window.create(sf::VideoMode(resolution.x, resolution.y), "Simple Game", sf::Style::Fullscreen);

    backgroundTexture.loadFromFile("images/die.jpg");
    backgroundSprite.setTexture(backgroundTexture);

}

void Game::start()
{
    sf::Clock clock;
    //main loop
    while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time dt = clock.restart();
        float dtAsSeconds = dt.asSeconds();

        input();
        update(dtAsSeconds);
        draw();
    }
}

void Game::input(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        window.close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        player.moveLeft();
    }
    else{
        player.stopLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        player.moveRight();
    }
    else{
        player.stopRight();
    }
}

void Game::update(float dtAsSeconds){
    player.update(dtAsSeconds);
}

void Game::draw(){
    window.clear(sf::Color::White);

    window.draw(backgroundSprite);
    window.draw(player.getSprite());

    window.display();
}