#include "Game.h"

#include "GlobalState.h"

Game::Game(){
    sf::Vector2f resolution;
    resolution.x = sf::VideoMode::getDesktopMode().width;
    resolution.y = sf::VideoMode::getDesktopMode().height;
    window.create(sf::VideoMode(resolution.x, resolution.y), "Simple Game");

    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
}

void Game::start() {
    
    auto& Glob = getGlobalState();

    Glob.addWindow<MenuWindow>(MenuWindow::Name);
    Glob.addWindow<SettingsWindow>(SettingsWindow::Name);
    Glob.addWindow<GameWindow>(GameWindow::Name);    
    Glob.setCurrWindow(MenuWindow::Name);

    while (window.isOpen()){

        sf::Event event;

        BaseWindow* CurrWindow = Glob.getCurrWindow();
        if (!CurrWindow) {
            window.close();
            continue;
        }

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        CurrWindow->input(window);
        CurrWindow->update(window);
        window.clear(sf::Color::Black);
        CurrWindow->draw(window);
        window.display();

    }
}
