#include "Game.h"
const int32 MS_PER_UPDATE = 16;
Game::Game(){
    windowSize.x = sf::VideoMode::getDesktopMode().width;
    windowSize.y = sf::VideoMode::getDesktopMode().height;
    window.create(sf::VideoMode(windowSize.x, windowSize.y), "Simple Game");

    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(120);
}

void Game::start() {
    
    auto& Glob = getGlobalState();

    Glob.addWindow<MenuWindow>(MenuWindow::Name);
    Glob.addWindow<SettingsWindow>(SettingsWindow::Name);
    Glob.addWindow<LevelWindow>(LevelWindow::Name);
    Glob.addWindow<GameWindow>(GameWindow::Name);

    Glob.setCurrWindow(MenuWindow::Name);
    
    int32 previous = clock.getElapsedTime().asMilliseconds();
    int32 lag = 0;
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

        int32 current = clock.getElapsedTime().asMilliseconds();
        int32 elapsed = current - previous;
        previous = current;
        lag += elapsed;

        CurrWindow->input(window, view);

        while (lag >= MS_PER_UPDATE) {
            CurrWindow->update(window, view, windowSize);
            window.setView(view);
            lag -= MS_PER_UPDATE;
        }

        window.clear(sf::Color::Black);
        CurrWindow->draw(window);
        window.display();
    }
}
