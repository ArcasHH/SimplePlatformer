#include "Game.h"
Game::Game(){
    //windowSize.x = sf::VideoMode::getDesktopMode().width;
    //windowSize.y = sf::VideoMode::getDesktopMode().height;
    windowSize.x = 1920;
    windowSize.y = 1080;
    window.create(sf::VideoMode(windowSize.x, windowSize.y), "Simple Game");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(frames);
}

void Game::start() {
    
    auto& Glob = getGlobalState();

    Glob.addWindow<MenuWindow>(MenuWindow::Name);
    Glob.addWindow<SettingsWindow>(SettingsWindow::Name);
    Glob.addWindow<LevelWindow>(LevelWindow::Name);
    Glob.addWindow<GameWindow>(GameWindow::Name);

    Glob.setCurrWindow(MenuWindow::Name);
    clock.restart();
    float loopTime = static_cast<float>(clock.getElapsedTime().asMilliseconds()+1)/frames;
    while (window.isOpen()){
        //clock.restart();
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
        
        
        CurrWindow->update(window, view, windowSize, loopTime);
        window.setView(view);

        window.clear(sf::Color::Black);
        CurrWindow->draw(window);
        window.display();
        clock.restart();
        loopTime = static_cast<float>(clock.getElapsedTime().asMilliseconds()+1)/frames;

    }
}
