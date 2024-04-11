#include "Windows.h"

void onExit() {
    auto& Glob = getGlobalState();
    Glob.setCurrWindow("exit");
}

void onStartGame() {
    auto& Glob = getGlobalState();
    Glob.setCurrWindow(GameWindow::Name);
}

void onSettings() {
    auto& Glob = getGlobalState();
    Glob.setCurrWindow(SettingsWindow::Name);
}

void onMenu() {
    auto& Glob = getGlobalState();
    Glob.setCurrWindow(MenuWindow::Name);
}
