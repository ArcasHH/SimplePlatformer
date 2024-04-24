#include "Windows.h"

void onExit() {
    auto& Glob = getGlobalState();
    Glob.setCurrWindow("exit");
}

void onStartGame(int& level, int l) {
    level = l;
    auto& Glob = getGlobalState();
    Glob.setCurrWindow(GameWindow::Name);
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

void onPause(bool &is_pause) {
    is_pause = false;
}


void updatePauseScreen(sf::View& view, std::vector<PushButton*>& Buttons, std::vector<Object*>& Objects) {
    sf::Vector2f view_center = view.getCenter();
    Objects[0]->sprite.setPosition(view_center.x - view.getSize().x / 2, view_center.y - view.getSize().y / 2);
    for (float i = 0; i < Buttons.size(); ++i) {
        PushButton* Button = Buttons[i];
        Button->setPosition(view_center.x + 128 * i - view.getSize().x / 4, view_center.y); // 128-96 = 32 - distance between buttons in pause screen
    }
}
void playMusic(sf::Music& music, std::vector<sf::Music*> musicvec) {
    if (music.getStatus() != sf::Music::Playing) {
        for (auto&& m : musicvec)
            m->stop();
        music.play();
    }
}

void upVolume(std::vector<sf::Music*> mvec) {
    for (auto&& m : mvec) {
        float vol = m->getVolume();
        if (vol <= 90)
            m->setVolume(vol + 10.f);
    }
}
void downVolume(std::vector<sf::Music*> mvec) {
    for (auto&& m : mvec) {
        float vol = m->getVolume();
        if (vol >= 10)
            m->setVolume(vol - 10.f);
    }
}
//for the level with the value l, set the music from mvec and upload it to the scene
void SetLevel(int& level,int l, sf::Music& music, std::vector<sf::Music*> mvec, GameScene*&gameScene) {
    if (level == l && music.getStatus() != sf::Music::Playing) {
        gameScene = NewGameScene("map/lvl" + std::to_string(level) + ".tmx");
        playMusic(std::ref(music), mvec);
        gameScene->playerBody->SetTransform(b2Vec2(35, 135), 0.f);//initial position of the player
    }
}