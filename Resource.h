#pragma once
#include "Windows.h"

namespace {

    BaseWindow w_menu;
    BaseWindow w_settings;
    GameWindow w_game;

    PushButton menu_exit("images/exit256.png", 100, 700, exit_button());
    PushButton menu_play("images/play256.png", 100, 100, game_button());
    PushButton menu_settings("images/settings256.png", 100, 400, settings_button());
    PushButton settings_menu("images/back256.png", 100, 700, menu_button());
    Object obj("images/die.jpg", 100, 100);

    void load_menu_objects() {
        w_menu.Buttons.push_back(&menu_play);
        w_menu.Buttons.push_back(&menu_settings);
        w_menu.Buttons.push_back(&menu_exit);
        
    }
    void load_settings_objects() {
        w_settings.Buttons.push_back(&settings_menu);
    }
    void load_game_objects() {
        w_game.Objects.push_back(&obj);
        w_game.Buttons.push_back(&settings_menu);
    }
}
