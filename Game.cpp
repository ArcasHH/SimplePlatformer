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
    BaseWindow w_curr;
    Object ob("images/exit.png", 0, 300);
    w_curr.Objects.push_back(&ob);
    PushButton b("images/exit256.png", 400, 400, true, false);
    PushButton b1("images/exit256.png", 400, 700, false, true);
    w_curr.Buttons.push_back(&b);
    w_curr.Buttons.push_back(&b1);
    BaseWindow w_next;
    PushButton b2("images/play256.png", 400, 400, true, false);
    PushButton b3("images/play256.png", 400, 700, false, true);
    w_next.Buttons.push_back(&b2);
    w_next.Buttons.push_back(&b3);

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

        if (w.is_w) {
            w = w_curr;
        }
        else {
            w = w_next;
        }

        input();
        update(dtAsSeconds);
        draw();
    }
}

void Game::input(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        window.close();
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        w.input(window);
    }
}

void Game::update(float dtAsSeconds){
    w.update(window);
}

void Game::draw(){
    window.clear(sf::Color::Black);

    w.draw(window);

    window.display();
}
