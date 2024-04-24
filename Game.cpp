#include "Game.h"

Game::Game(){
    windowSize.x = sf::VideoMode::getDesktopMode().width;
    windowSize.y = sf::VideoMode::getDesktopMode().height;
    window.create(sf::VideoMode(windowSize.x, windowSize.y), "Simple Game");

    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(60);
}

void Game::start() {
    
    auto& Glob = getGlobalState();

    Glob.addWindow<MenuWindow>(MenuWindow::Name);
    Glob.addWindow<SettingsWindow>(SettingsWindow::Name);
    Glob.addWindow<LevelWindow>(LevelWindow::Name);
    Glob.addWindow<GameWindow>(GameWindow::Name);

    Glob.setCurrWindow(MenuWindow::Name);
    
    g_clock.restart();
    while (window.isOpen()){
        sf::Event event;

        BaseWindow* CurrWindow = Glob.getCurrWindow();
        if (!CurrWindow) {
            window.close();
            break;
        }
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
                break;
            }
        }

        CurrWindow->input(window, view);
       
        CurrWindow->update(window, view, windowSize);
        window.setView(view);

        window.clear(sf::Color::Black);
        CurrWindow->draw(window);
        window.display();
    }
}
