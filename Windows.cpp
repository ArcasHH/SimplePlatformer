#include "Windows.h"

void onExit() {
    auto& Glob = getGlobalState();
    Glob.setCurrWindow("exit");
}

void onStartGame1() {
    auto& Glob = getGlobalState();
    Glob.setCurrWindow(GameWindow1::Name);
}
void onStartGame2() {
    auto& Glob = getGlobalState();
    Glob.setCurrWindow(GameWindow2::Name);
}

void onSettings() {
    auto& Glob = getGlobalState();
    Glob.setCurrWindow(SettingsWindow::Name);
}
void onLevel() {
    auto& Glob = getGlobalState();
    Glob.setCurrWindow(LevelWindow::Name);
}

void onMenu() {
    auto& Glob = getGlobalState();
    Glob.setCurrWindow(MenuWindow::Name);
}


void updatePauseScreen(sf::View& view, std::vector<PushButton*>& Buttons, std::vector<Object*>& Objects) {
    sf::Vector2f view_center = view.getCenter();
    Objects[0]->sprite.setPosition(view_center.x - view.getSize().x / 2, view_center.y - view.getSize().y / 2);
    for (float i = 0; i < Buttons.size(); ++i) {
        PushButton* Button = Buttons[i];
        Button->setPosition(view_center.x + 128 * i - view.getSize().x / 4, view_center.y);
    }
}
void playMusic(sf::Music& music, std::vector<sf::Music*> musicvec) {
    if (music.getStatus() != sf::Music::Playing) {
        for (auto&& m : musicvec)
            m->stop();
        music.play();
    }
}