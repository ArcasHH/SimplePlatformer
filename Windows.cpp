#include "GlobalState.h"

#include "Windows.h"


void MenuWindow::onExit() {
    auto& Glob = getGlobalState();
    Glob.setCurrWindow("exit");
}

void MenuWindow::onStartGame() {
    auto& Glob = getGlobalState();
    Glob.setCurrWindow(GameWindow::Name);
}
void MenuWindow::onStartGame2() {
    auto& Glob = getGlobalState();
    Glob.setCurrWindow("game2");
}

void MenuWindow::onSettings() {
    auto& Glob = getGlobalState();
    Glob.setCurrWindow(SettingsWindow::Name);
}

void GameWindow::onMenu() {
    auto& Glob = getGlobalState();
    Glob.setCurrWindow(MenuWindow::Name);
}

void SettingsWindow::onMenu() {
    auto& Glob = getGlobalState();
    Glob.setCurrWindow(MenuWindow::Name);
}
