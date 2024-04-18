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

