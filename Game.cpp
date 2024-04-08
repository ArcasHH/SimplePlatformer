#include "Game.h"

Game::Game(){
    frames = 60;
    
    sf::Vector2f resolution;
    resolution.x = sf::VideoMode::getDesktopMode().width;
    resolution.y = sf::VideoMode::getDesktopMode().height;
    window.create(sf::VideoMode(resolution.x, resolution.y), "Simple Game");
    window.setVerticalSyncEnabled(true);

}

void Game::start(){

    Object ob("images/exit.png", 0, 300);
    w.Objects.push_back(&ob);
    Object ob1("images/exit.png", 300, 300);
    w.Objects.push_back(&ob1);
    PushButton b("images/exit256.png", 400, 400);
    w.Buttons.push_back(&b);

    sf::Clock clock;
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
}

void Game::update(float dtAsSeconds){
    //player.update(dtAsSeconds);
    for (auto&& obj : w.Buttons) {
        obj->update(window);
    }
}

void Game::draw(){
    window.clear(sf::Color::Black);
    for (auto&& obj : w.Objects) {
        obj->draw(window);
    }
    for (auto&& obj : w.Buttons) {
        obj->draw(window);
    }
    window.display();
}
