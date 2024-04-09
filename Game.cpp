#include "Game.h"

Game::Game(){
    frames = 60;
    is_w = isW(0, 1, 0);
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
    PushButton b("images/exit256.png", 400, 400, exit_button());
    PushButton b1("images/exit256.png", 400, 700, menu_button());
    w_curr.Buttons.push_back(&b);
    w_curr.Buttons.push_back(&b1);
    BaseWindow w_next;
    PushButton b2("images/play256.png", 700, 400, exit_button());
    PushButton b3("images/play256.png", 700, 700, settings_button());
    w_next.Buttons.push_back(&b2);
    w_next.Buttons.push_back(&b3);
    w = &w_curr;
    bool once_menu = true;
    bool once_settings = true;

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
        
        if (is_w.is_menu && once_menu) {
            w = &w_next;
            once_menu = false;
            once_settings = true;
        }
        if (is_w.is_settings && once_settings) {
            w = &w_curr;
            once_settings = false;
            once_menu = true;
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
        (*w).input(window, is_w);
    }
}

void Game::update(float dtAsSeconds){
    (*w).update(window);
}

void Game::draw(){
    window.clear(sf::Color::Black);

    (*w).draw(window);

    window.display();
}
