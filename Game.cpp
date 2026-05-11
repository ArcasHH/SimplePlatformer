#include "Game.h"
Game::Game() {
    windowSize.x = static_cast<float>(1920);
    windowSize.y = static_cast<float>(1080);
    window.create(sf::VideoMode(1920, 1080), "Simple Game");
    window.setVerticalSyncEnabled(false);
    window.setFramerateLimit(GameScene::frames);
}

void Game::start() {
    
    auto& Glob = getGlobalState();

    Glob.addWindow<SettingsWindow>(SettingsWindow::Name);
    GameWindow* GW = Glob.addWindow<GameWindow>(GameWindow::Name);
    Glob.addWindow<LevelWindow>(LevelWindow::Name, *GW);
    Glob.addWindow<MenuWindow>(MenuWindow::Name, *GW);

    Glob.setCurrWindow(MenuWindow::Name);

    while (window.isOpen()) {
        BaseWindow* CurrWindow = Glob.getCurrWindow();
        if (!CurrWindow) {
            window.close();
            return;
        }
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
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
