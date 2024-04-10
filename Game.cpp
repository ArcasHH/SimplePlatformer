#include "Game.h"

Game::Game(){
    sf::Vector2f resolution;
    resolution.x = sf::VideoMode::getDesktopMode().width;
    resolution.y = sf::VideoMode::getDesktopMode().height;
    window.create(sf::VideoMode(resolution.x, resolution.y), "Simple Game");

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
}

void Game::start(){
    
    load_menu_objects();
    load_settings_objects();
    load_game_objects();
    
    w = &w_menu;

    while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        input();
        update();
        draw();
    }
}

void Game::input(){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        window.close();
    }
    (*w).input(window, is_w);
}

void Game::update(){
    if (is_w.is_menu) {
        w = &w_menu;
    }
    if (is_w.is_settings) {
        w = &w_settings;
    }
    if (is_w.is_game) {
        w = &w_game;
    }

    (*w).update(window);
}

void Game::draw(){
    window.clear(sf::Color::Black);
    (*w).draw(window);
    window.display();
}
